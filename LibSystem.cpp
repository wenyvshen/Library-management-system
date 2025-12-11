#include <iostream>
#include <fstream>
#include <cstring>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;

void System::addUser(const User& user)
{
    users.push_back(user);
    SaveData(); // 立即持久化，防止丢数据
}

// 添加图书；若 ISBN 已存在则累加数量
void System::addBook(const Book& book)
{
    bool merged = false; // 是否已合并到现有库存
    for (auto& b : books)
    {
        if (b.getIsbn() == book.getIsbn())
        {
            b.setQuantity(b.getQuantity() + book.getQuantity());
            merged = true;
            break;
        }
    }
    if (!merged)
    {
        books.push_back(book);
    }
    SaveData();
}

// 展示全部图书
void System::displayAllBooks() const
{
    for (const auto& book : books)
    {
        book.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

// 展示全部用户
void System::displayAllUsers() const
{
    for (const auto& user : users)
    {
        user.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

// 用户登录校验
void System::UserLogin(const string& username, const string& password)
{
     bool found = false;
    for (auto& user : users)
    {
        if (user.getName() == username)
        {
            if(password == user.getPassword())
            {
                cout << "用户 " << username << " 登录成功。" << endl;
                user.setisLoggedIn(true);
                found = true;
                break;
            }
            else
            {
                found = true;
                cout << "用户 " << username << " 的密码错误。" << endl;
                break;
            }
        }
    }
    if (!found)
        {
            cout << "未找到用户 " << username << "。" << endl;
        }
}

// 用户登出
void System::UserLogout(const string& username)
{
    for (auto& user : users)
    {
        if (user.getName() == username)
        {
            cout << "用户 " << username << " 已退出登录。" << endl;
            user.setisLoggedIn(false);
            break;
        }
    }
}

// 保存所有数据（覆盖文件）
void System::SaveData() const
{
    // 写书
    std::fstream bf(R"(F:\library\Library-management-system\Book.dat)",
                    std::ios::out | std::ios::binary | std::ios::trunc);
    if (!bf.is_open()) {
        std::cerr << "无法打开 Book.dat 进行写入" << std::endl;
    } else {
        for (const auto& b : books) {
            char isbn[20] = {0}, title[100] = {0}, author[50] = {0};
            int quantity = b.getQuantity();
            std::strncpy(isbn,  b.getIsbn().c_str(),  sizeof(isbn)  - 1);
            std::strncpy(title, b.getTitle().c_str(), sizeof(title) - 1);
            std::strncpy(author,b.getAuthor().c_str(),sizeof(author)- 1);
            bf.write(isbn,   sizeof(isbn));
            bf.write(title,  sizeof(title));
            bf.write(author, sizeof(author));
            bf.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
        }
    }

    // 写用户
    std::fstream uf(R"(F:\library\Library-management-system\User.dat)",
                    std::ios::out | std::ios::binary | std::ios::trunc);
    if (!uf.is_open()) {
        std::cerr << "无法打开 User.dat 进行写入" << std::endl;
    } else {
        for (const auto& u : users) {
            char name[50] = {0}, pwd[50] = {0};
            char history[100][50] = {{0}};
            std::strncpy(name, u.getName().c_str(), sizeof(name) - 1);
            std::strncpy(pwd,  u.getPassword().c_str(), sizeof(pwd) - 1);
            for (int i = 0; i < 100; ++i) {
                auto entry = u.getHistoryEntry(i);
                if (!entry.empty()) {
                    std::strncpy(history[i], entry.c_str(), sizeof(history[i]) - 1);
                }
            }
            uf.write(name, sizeof(name));
            uf.write(pwd,  sizeof(pwd));
            uf.write(reinterpret_cast<const char*>(history), sizeof(history));
        }
    }
}

// 读取所有数据（覆盖内存中的向量）
void System::LoadData()
{
    books.clear();
    users.clear();

    // 读书
    std::fstream bf(R"(F:\library\Library-management-system\Book.dat)",
                    std::ios::binary | std::ios::in);
    if (bf.is_open()) {
        while (true) {
            char isbn[20], title[100], author[50];
            int quantity;
            if (!bf.read(isbn, sizeof(isbn))) break;
            if (!bf.read(title, sizeof(title))) break;
            if (!bf.read(author, sizeof(author))) break;
            if (!bf.read(reinterpret_cast<char*>(&quantity), sizeof(quantity))) break;
            books.emplace_back(std::string(isbn), std::string(title), std::string(author), quantity);
        }
    }

    // 读用户
    std::fstream uf(R"(F:\library\Library-management-system\User.dat)",
                    std::ios::binary | std::ios::in);
    if (uf.is_open()) {
        while (true) {
            char name[50], pwd[50];
            char history[100][50];
            if (!uf.read(name, sizeof(name))) break;
            if (!uf.read(pwd,  sizeof(pwd)))  break;
            if (!uf.read(reinterpret_cast<char*>(history), sizeof(history))) break;
            users.emplace_back(std::string(name), std::string(pwd));
            User& u = users.back();
            for (int i = 0; i < 100; ++i) {
                if (history[i][0] != '\0') {
                    u.setHistoryEntry(i, std::string(history[i]));
                }
            }
        }
    }
}

// 判断用户是否已登录
bool System::isUserLoggedIn(const string& username) const
{
    bool status = false;
    for (const auto& user : users)
    {
        if (user.getName() == username)
        {
            return user.getisLoggedIn();
        }
    }
    return false;
}

// 获取当前已登录的用户名（若无则返回空）
string System::getLoggedInUsername() const
{
    for (const auto& user : users)
    {
        if (user.getisLoggedIn())
        {
            return user.getName();
        }
    }
    return "";
}

// 获取全部图书集合
const std::vector<Book>& System::getBooks() const {
    return books;
}

// 按书名关键词搜索，返回匹配的图书列表
std::vector<Book> System::searchBooksByTitleKeyword(const string& keyword) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.getTitle().find(keyword) != string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

// 按作者精确搜索，返回匹配的图书列表
std::vector<Book> System::searchBooksByAuthor(const string& author) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.getAuthor() == author) {
            result.push_back(book);
        }
    }
    return result;
}

void System::borrowBook(const string& username, const string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            if (book.getQuantity() > 0) {
                book.setQuantity(book.getQuantity() - 1);
                cout << "图书《" << book.getTitle() << "》借阅成功！" << endl;
                for (auto& u : users) {
                    if (u.getName() == username) {
                        u.addToHistory(isbn);
                        break;
                    }
                }
                SaveData();
            } else {
                cout << "图书《" << book.getTitle() << "》库存不足，无法借阅！" << endl;
            }
            return;
        }
    }
    cout << "未找到ISBN码为 '" << isbn << "' 的图书。" << endl;
}

const std::vector<User>& System::getUsers() const {
    return users;
}