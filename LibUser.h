#ifndef LIBUSER_H
#define LIBUSER_H
#include <string>
using namespace std;
class User
{
    public:
        User() = default;
        User(const string name, const string password);
        void displayInfo() const;
        void saveToFile() const;
        void loadFromFile();
        string getName() const;
        string getPassword() const;
        void setisLoggedIn(bool status);
        bool getisLoggedIn() const;
        
    private:
        string name;  // 用户名
        string password; // 密码
        string history[100]; // 借阅历史
        bool isLoggedIn = false; // 登录状态




};

#endif