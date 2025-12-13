#ifndef LIBUSER_H
#define LIBUSER_H
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

struct BorrowRecord {
    string isbn;
    time_t borrowDate;
    int renewCount;
};

class User
{
    public:
        // 默认构造
        User() = default;
        // 构造：设置用户名与密码
        User(const string name, const string password);
        virtual ~User() = default;

        // 纯虚函数接口
        virtual int getMaxBorrowCount() const = 0;
        virtual int getMaxBorrowDays() const = 0;
        virtual bool canBorrowSpecial() const = 0;
        virtual int getMaxRenewals() const = 0;
        virtual string getType() const = 0; // "Student" or "Teacher"

        // 展示用户信息
        virtual void displayInfo() const;
        
        // 获取用户名
        string getName() const;
        // 获取密码
        string getPassword() const;
        // 设置登录状态
        void setisLoggedIn(bool status);
        // 获取登录状态
        bool getisLoggedIn() const;
        
        // 借阅管理
        void addToHistory(const string& isbn);
        // 获取借阅记录列表
        const vector<BorrowRecord>& getHistory() const;
        // 删除历史中首个匹配 ISBN
        void deleteFromHistory(const string& isbn);
        // 续借
        bool renewBook(const string& isbn);
        
        // 用于文件加载
        void addHistoryEntry(const BorrowRecord& record);

    protected:
        string name;  // 用户名
        string password; // 密码
        vector<BorrowRecord> history; // 借阅历史
        bool isLoggedIn = false; // 登录状态
};

class Student : public User
{
    public:
        Student() = default;
        Student(const string name, const string password);
        
        int getMaxBorrowCount() const override { return 8; }
        int getMaxBorrowDays() const override { return 30; }
        bool canBorrowSpecial() const override { return false; }
        int getMaxRenewals() const override { return 1; }
        string getType() const override { return "Student"; }
        
        void displayInfo() const override;
};

class Teacher : public User
{
    public:
        Teacher() = default;
        Teacher(const string name, const string password);
        
        int getMaxBorrowCount() const override { return 15; }
        int getMaxBorrowDays() const override { return 60; }
        bool canBorrowSpecial() const override { return true; }
        int getMaxRenewals() const override { return 3; }
        string getType() const override { return "Teacher"; }
        
        void displayInfo() const override;
};

#endif