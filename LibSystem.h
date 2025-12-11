#ifndef LIBSYSTEM_H
#define LIBSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "LibBook.h"
#include "LibUser.h"
using namespace std;

class System
{
public:
    // 默认构造
    System() = default;
    // 添加图书
    void addBook(const Book& book);
    // 展示全部图书
    void displayAllBooks() const;    
    // 添加用户
    void addUser(const User& user);
    // 展示全部用户
    void displayAllUsers() const;
    // 用户登录
    void UserLogin(const string& username, const string& password);
    // 用户登出
    void UserLogout(const string& username);
    // 保存数据到文件
    void SaveData() const;
    // 从文件加载数据
    void LoadData();
    // 判断指定用户是否登录
    bool isUserLoggedIn(const string& username) const;
    // 获取当前登录用户名
    string getLoggedInUsername() const;
    // 获取全部图书集合
    const std::vector<Book>& getBooks() const;
    // 按书名关键词搜索，返回匹配列表
    std::vector<Book> searchBooksByTitleKeyword(const string& keyword) const;
    // 按作者精确搜索，返回匹配列表
    std::vector<Book> searchBooksByAuthor(const string& author) const;
    void borrowBook(const string& username, const string& isbn);
    const std::vector<User>& getUsers() const;
private:
    vector<Book> books;  // 图书集合
    vector<User> users;  // 用户集合

};


#endif