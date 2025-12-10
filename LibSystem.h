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
    System() = default;
    void addBook(const Book& book);
    void displayAllBooks() const;    
    void addUser(const User& user);
    void displayAllUsers() const;
    void UserLogin(const string& username, const string& password);
    void UserLogout(const string& username);
    void SaveData() const;
    void LoadData();
    bool isUserLoggedIn(const string& username) const;
    string getLoggedInUsername() const;
private:
    vector<Book> books;  // 图书集合
    vector<User> users;  // 用户集合

};


#endif