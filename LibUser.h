#ifndef LIBUSER_H
#define LIBUSER_H
#include <string>
using namespace std;
class User
{
    public:
        User() = default;
        User(string name): name(name) {};
        void displayInfo() const;
    private:
        string name;  // 用户名




};

#endif