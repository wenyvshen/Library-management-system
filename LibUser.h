#ifndef LIBUSER_H
#define LIBUSER_H
#include <string>
using namespace std;
class User
{
    public:
        // 默认构造
        User() = default;
        // 构造：设置用户名与密码
        User(const string name, const string password);
        // 展示用户信息
        void displayInfo() const;
        // 获取用户名
        string getName() const;
        // 获取密码
        string getPassword() const;
        // 设置登录状态
        void setisLoggedIn(bool status);
        // 获取登录状态
        bool getisLoggedIn() const;
        // 追加一条借阅历史（ISBN）
        void addToHistory(const string& isbn);
        // 获取指定下标的借阅历史（空则返回空字符串）
        string getHistoryEntry(int idx) const;
        // 设置指定下标的借阅历史（用于加载文件时恢复）
        void setHistoryEntry(int idx, const string& val);
        // 删除历史中首个匹配 ISBN
        void deleteFromHistory(const string& isbn);
        
    private:
        string name;  // 用户名
        string password; // 密码
        string history[100]; // 借阅历史
        bool isLoggedIn = false; // 登录状态




};

#endif