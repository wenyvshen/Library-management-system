#include "LibUser.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

User::User(const string name, const string password)
    : name(name), password(password), isLoggedIn(false) {}

// 展示用户基本信息
void User::displayInfo() const
{
    cout << "用户名：" << name << endl;
}

// 获取用户名
string User::getName() const
{
    return name;
}

// 获取密码
string User::getPassword() const
{
    return password;
}

// 设置登录状态
void User::setisLoggedIn(bool status)
{
    isLoggedIn = status;
}

// 获取登录状态
bool User::getisLoggedIn() const
{
    return isLoggedIn;
}

void User::addToHistory(const string& isbn)
{
    for (int i = 0; i < 100; ++i) {
        if (history[i].empty()) {
            history[i] = isbn;
            break;
        }
    }
}

string User::getHistoryEntry(int idx) const
{
    return (idx >=0 && idx < 100) ? history[idx] : "";
}

void User::setHistoryEntry(int idx, const string& val)
{
    if (idx >=0 && idx < 100) history[idx] = val;
}   

// 从历史里删除匹配的 ISBN（只删第一条）
void User::deleteFromHistory(const string& isbn)
{
    for (int i = 0; i < 100; ++i) {
        if (history[i] == isbn) {
            history[i] = "";
            break;
        }
    }
}