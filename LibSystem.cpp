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

void System::addBook(const Book& book)
{
    books.push_back(book);
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
    for (const auto& user : users)
    {
        user.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

void System::UserLogin(const string& username, const string& password)
{
     bool found = false;
    for (auto& user : users)
    {
        if (user.getName() == username)
        {
            if(password == user.getPassword())
            {
                cout << "User " << username << " logged in." << endl;
                user.setisLoggedIn(true);
                found = true;
                break;
            }
            else
            {
                cout << "Incorrect password for user " << username << "." << endl;
                break;
            }
        }
    }
    if (!found)
        {
            cout << "User " << username << " not found." << endl;
        }
}

void System::UserLogout(const string& username)
{
    for (auto& user : users)
    {
        if (user.getName() == username)
        {
            cout << "User " << username << " logged out." << endl;
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
            std::strncpy(isbn,  b.getIsbn().c_str(),  sizeof(isbn)  - 1);
            std::strncpy(title, b.getTitle().c_str(), sizeof(title) - 1);
            std::strncpy(author,b.getAuthor().c_str(),sizeof(author)- 1);
            bf.write(isbn,   sizeof(isbn));
            bf.write(title,  sizeof(title));
            bf.write(author, sizeof(author));
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
            std::strncpy(name, u.getName().c_str(), sizeof(name) - 1);
            std::strncpy(pwd,  u.getPassword().c_str(), sizeof(pwd) - 1);
            uf.write(name, sizeof(name));
            uf.write(pwd,  sizeof(pwd));
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
            if (!bf.read(isbn, sizeof(isbn))) break;
            if (!bf.read(title, sizeof(title))) break;
            if (!bf.read(author, sizeof(author))) break;
            books.emplace_back(std::string(isbn), std::string(title), std::string(author));
        }
    }

    // 读用户
    std::fstream uf(R"(F:\library\Library-management-system\User.dat)",
                    std::ios::binary | std::ios::in);
    if (uf.is_open()) {
        while (true) {
            char name[50], pwd[50];
            if (!uf.read(name, sizeof(name))) break;
            if (!uf.read(pwd,  sizeof(pwd)))  break;
            users.emplace_back(std::string(name), std::string(pwd));
        }
    }
}

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