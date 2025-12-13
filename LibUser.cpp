#include "LibUser.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

User::User(const string name, const string password)
    : name(name), password(password), isLoggedIn(false) {}

void User::displayInfo() const
{
    cout << "用户名：" << name << endl;
    cout << "类型：" << getType() << endl;
    cout << "最大借阅数：" << getMaxBorrowCount() << endl;
    cout << "最大借阅天数：" << getMaxBorrowDays() << endl;
}

string User::getName() const
{
    return name;
}

string User::getPassword() const
{
    return password;
}

void User::setisLoggedIn(bool status)
{
    isLoggedIn = status;
}

bool User::getisLoggedIn() const
{
    return isLoggedIn;
}

void User::addToHistory(const string& isbn)
{
    BorrowRecord record;
    record.isbn = isbn;
    record.borrowDate = time(nullptr);
    record.renewCount = 0;
    history.push_back(record);
}

const vector<BorrowRecord>& User::getHistory() const
{
    return history;
}

void User::deleteFromHistory(const string& isbn)
{
    for (auto it = history.begin(); it != history.end(); ++it) {
        if (it->isbn == isbn) {
            history.erase(it);
            break;
        }
    }
}

bool User::renewBook(const string& isbn)
{
    for (auto& record : history) {
        if (record.isbn == isbn) {
            if (record.renewCount < getMaxRenewals()) {
                record.renewCount++;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void User::addHistoryEntry(const BorrowRecord& record)
{
    history.push_back(record);
}

// Student Implementation
Student::Student(const string name, const string password)
    : User(name, password) {}

void Student::displayInfo() const
{
    User::displayInfo();
    cout << "身份：学生" << endl;
}

// Teacher Implementation
Teacher::Teacher(const string name, const string password)
    : User(name, password) {}

void Teacher::displayInfo() const
{
    User::displayInfo();
    cout << "身份：教师" << endl;
}