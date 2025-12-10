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
        void saveToFile() const;
        void loadFromFile();
        
    private:
        string name;  // 用户名




};

#endif