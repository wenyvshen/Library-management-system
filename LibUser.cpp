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

// 获取指定下标的借阅历史（已在头文件内联，保留此处空行占位以便可读性）
void User::addToHistory(const string& isbn)
{
    for (int i = 0; i < 100; ++i) {
        if (history[i].empty()) {
            history[i] = isbn;
            break;
        }
    }
}

// 获取指定下标的借阅历史（空则返回空字符串）
string User::getHistoryEntry(int idx) const
{
    return (idx >=0 && idx < 100) ? history[idx] : "";
}

// 设置指定下标的借阅历史（用于加载文件时恢复）
void User::setHistoryEntry(int idx, const string& val)
{
    if (idx >=0 && idx < 100) history[idx] = val;
}   