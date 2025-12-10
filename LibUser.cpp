#include "LibUser.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

User::User(const string name, const string password)
    : name(name), password(password), isLoggedIn(false) {}

void User::displayInfo() const
{
    cout << "User Name: " << name << endl;
}

/*void User::saveToFile() const
{
    char t_name[50];
    strcpy(t_name, name.c_str());

    fstream file;
    file.open(R"(F:\library\Library-management-system\User.dat)", ios::trunc | ios::binary);
    if (file.is_open() == false)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.write((const char*)t_name, sizeof(t_name));
    file.close();
}

void User::loadFromFile()
{
    char t_name[50];

    fstream file;
    file.open(R"(F:\library\Library-management-system\User.dat)", ios::in | ios::binary);
    if (file.is_open() == false)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.read(t_name, sizeof(t_name));
    file.close();

    name = string(t_name);
}*/

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
