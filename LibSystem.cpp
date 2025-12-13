#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "LibBook.h"
#include "LibSystem.h"

using namespace std;

System::~System() {
    for (User* user : users) {
        delete user;
    }
    users.clear();
}

void System::addUser(User* user)
{
    users.push_back(user);
    SaveData();
}

void System::addBook(const Book& book)
{
    bool merged = false;
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

void System::displayAllBooks() const
{
    for (const auto& book : books)
    {
        book.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

void System::displayAllUsers() const
{
    for (const auto* user : users)
    {
        user->displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

User* System::findUser(const string& username) const {
    for (auto* user : users) {
        if (user->getName() == username) {
            return user;
        }
    }
    return nullptr;
}

Book* System::findBook(const string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

void System::UserLogin(const string& username, const string& password)
{
    User* user = findUser(username);
    if (user) {
        if (user->getPassword() == password) {
            cout << "用户 " << username << " 登录成功。" << endl;
            user->setisLoggedIn(true);
        } else {
            cout << "用户 " << username << " 的密码错误。" << endl;
        }
    } else {
        cout << "未找到用户 " << username << "。" << endl;
    }
}

void System::UserLogout(const string& username)
{
    User* user = findUser(username);
    if (user) {
        cout << "用户 " << username << " 已退出登录。" << endl;
        user->setisLoggedIn(false);
    }
}

void System::SaveData() const
{
    // 写书
    std::fstream bf(R"(F:\library\Library-management-system\Book.dat)", std::ios::out | std::ios::binary | std::ios::trunc);
    if (!bf.is_open()) {
        std::cerr << "无法打开 Book.dat 进行写入" << std::endl;
    } else {
        for (const auto& b : books) {
            char isbn[20] = {0}, title[100] = {0}, author[50] = {0};
            int quantity = b.getQuantity();
            bool isSpecial = b.getIsSpecial();
            
            std::strncpy(isbn,  b.getIsbn().c_str(),  sizeof(isbn)  - 1);
            std::strncpy(title, b.getTitle().c_str(), sizeof(title) - 1);
            std::strncpy(author,b.getAuthor().c_str(),sizeof(author)- 1);
            
            bf.write(isbn,   sizeof(isbn));
            bf.write(title,  sizeof(title));
            bf.write(author, sizeof(author));
            bf.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
            bf.write(reinterpret_cast<const char*>(&isSpecial), sizeof(isSpecial));
        }
        bf.close();
    }

    // 写用户
    std::fstream uf(R"(F:\library\Library-management-system\User.dat)", std::ios::out | std::ios::binary | std::ios::trunc);
    if (!uf.is_open()) {
        std::cerr << "无法打开 User.dat 进行写入" << std::endl;
    } else {
        for (const auto* u : users) {
            // 写入类型标识
            int type = (u->getType() == "Student") ? 1 : 2;
            uf.write(reinterpret_cast<const char*>(&type), sizeof(type));

            char name[50] = {0}, pwd[50] = {0};
            std::strncpy(name, u->getName().c_str(), sizeof(name) - 1);
            std::strncpy(pwd,  u->getPassword().c_str(), sizeof(pwd) - 1);
            
            uf.write(name, sizeof(name));
            uf.write(pwd,  sizeof(pwd));

            // 写入借阅历史
            const auto& history = u->getHistory();
            int historyCount = static_cast<int>(history.size());
            uf.write(reinterpret_cast<const char*>(&historyCount), sizeof(historyCount));

            for (const auto& h : history) {
                char h_isbn[20] = {0};
                std::strncpy(h_isbn, h.isbn.c_str(), sizeof(h_isbn) - 1);
                uf.write(h_isbn, sizeof(h_isbn));
                uf.write(reinterpret_cast<const char*>(&h.borrowDate), sizeof(h.borrowDate));
                uf.write(reinterpret_cast<const char*>(&h.renewCount), sizeof(h.renewCount));
            }
        }
        uf.close();
    }
}

void System::LoadData()
{
    // 清理现有数据
    for (User* u : users) delete u;
    users.clear();
    books.clear();

    // 读书
    std::fstream bf(R"(F:\library\Library-management-system\Book.dat)", std::ios::binary | std::ios::in);
    if (bf.is_open()) {
        // 获取文件大小以判断循环结束（或者尝试读取直到失败）
        bf.peek(); // 尝试读取一个字符
        while (bf.good()) {
            char isbn[20], title[100], author[50];
            int quantity;
            bool isSpecial;
            
            if (!bf.read(isbn, sizeof(isbn))) break;
            if (!bf.read(title, sizeof(title))) break;
            if (!bf.read(author, sizeof(author))) break;
            if (!bf.read(reinterpret_cast<char*>(&quantity), sizeof(quantity))) break;
            if (!bf.read(reinterpret_cast<char*>(&isSpecial), sizeof(isSpecial))) break;
            
            books.emplace_back(std::string(isbn), std::string(title), std::string(author), quantity, isSpecial);
            bf.peek();
        }
        bf.close();
    }

    // 读用户
    std::fstream uf(R"(F:\library\Library-management-system\User.dat)", std::ios::binary | std::ios::in);
    if (uf.is_open()) {
        uf.peek();
        while (uf.good()) {
            int type;
            if (!uf.read(reinterpret_cast<char*>(&type), sizeof(type))) break;

            char name[50], pwd[50];
            if (!uf.read(name, sizeof(name))) break;
            if (!uf.read(pwd,  sizeof(pwd)))  break;

            User* newUser = nullptr;
            if (type == 1) newUser = new Student(name, pwd);
            else if (type == 2) newUser = new Teacher(name, pwd);

            int historyCount;
            if (!uf.read(reinterpret_cast<char*>(&historyCount), sizeof(historyCount))) {
                delete newUser;
                break;
            }

            if (newUser) {
                for (int i = 0; i < historyCount; ++i) {
                    BorrowRecord rec;
                    char h_isbn[20];
                    if (!uf.read(h_isbn, sizeof(h_isbn))) break;
                    if (!uf.read(reinterpret_cast<char*>(&rec.borrowDate), sizeof(rec.borrowDate))) break;
                    if (!uf.read(reinterpret_cast<char*>(&rec.renewCount), sizeof(rec.renewCount))) break;
                    
                    rec.isbn = h_isbn;
                    newUser->addHistoryEntry(rec);
                }
                users.push_back(newUser);
            } else {
                // 如果类型未知，跳过历史记录数据
                for (int i = 0; i < historyCount; ++i) {
                    char tempIsbn[20];
                    time_t tempDate;
                    int tempRenew;
                    uf.read(tempIsbn, sizeof(tempIsbn));
                    uf.read(reinterpret_cast<char*>(&tempDate), sizeof(tempDate));
                    uf.read(reinterpret_cast<char*>(&tempRenew), sizeof(tempRenew));
                }
            }
            uf.peek();
        }
        uf.close();
    }
}

bool System::isUserLoggedIn(const string& username) const
{
    User* user = findUser(username);
    return user ? user->getisLoggedIn() : false;
}

string System::getLoggedInUsername() const
{
    for (const auto* user : users) {
        if (user->getisLoggedIn()) return user->getName();
    }
    return "";
}

const std::vector<Book>& System::getBooks() const
{
    return books;
}

std::vector<Book> System::searchBooksByTitleKeyword(const string& keyword) const
{
    vector<Book> result;
    for (const auto& book : books) {
        if (book.getTitle().find(keyword) != string::npos) {
            result.push_back(book);
        }
    }
    return result;
}

std::vector<Book> System::searchBooksByAuthor(const string& author) const
{
    vector<Book> result;
    for (const auto& book : books) {
        if (book.getAuthor() == author) {
            result.push_back(book);
        }
    }
    return result;
}

void System::borrowBook(const string& username, const string& isbn)
{
    User* user = findUser(username);
    Book* book = findBook(isbn);

    if (!user) { std::cout << "用户不存在" << std::endl; return; }
    if (!book) { std::cout << "图书不存在" << std::endl; return; }

    if (book->getQuantity() <= 0) {
        std::cout << "库存不足" << std::endl;
        return;
    }

    // 权限检查
    if (user->getHistory().size() >= user->getMaxBorrowCount()) {
        std::cout << "已达最大借阅数量限制 (" << user->getMaxBorrowCount() << "本)" << std::endl;
        return;
    }

    if (book->getIsSpecial() && !user->canBorrowSpecial()) {
        std::cout << "该用户无权借阅特殊图书" << std::endl;
        return;
    }

    // 借阅成功
    book->setQuantity(book->getQuantity() - 1);
    user->addToHistory(isbn);
    std::cout << "借阅成功！" << std::endl;
    SaveData();
}

void System::returnBook(const string& username, const string& isbn)
{
    User* user = findUser(username);
    Book* book = findBook(isbn);

    if (!user) { std::cout << "用户不存在" << std::endl; return; }
    
    // 检查用户是否借了这本书
    bool borrowed = false;
    for (const auto& rec : user->getHistory()) {
        if (rec.isbn == isbn) {
            borrowed = true;
            break;
        }
    }

    if (!borrowed) {
        std::cout << "未找到该借阅记录" << std::endl;
        return;
    }

    user->deleteFromHistory(isbn);
    if (book) {
        book->setQuantity(book->getQuantity() + 1);
    } else {
        // 书可能被删了，或者数据不一致，但还是允许还书
        std::cout << "警告：归还的图书在系统中未找到，但借阅记录已清除。" << std::endl;
    }
    std::cout << "归还成功！" << std::endl;
    SaveData();
}

void System::renewBook(const string& username, const string& isbn)
{
    User* user = findUser(username);
    if (!user) { cout << "用户不存在" << endl; return; }

    if (user->renewBook(isbn)) {
        cout << "续借成功！" << endl;
        SaveData();
    } else {
        cout << "续借失败：可能已达最大续借次数或未找到借阅记录。" << endl;
    }
}

const std::vector<User*>& System::getUsers() const
{
    return users;
}


