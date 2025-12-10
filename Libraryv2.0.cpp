#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;
int main()
{
    System sys;
    sys.LoadData();
   int i;
   while (1)
   {
    string Loginname = sys.getLoggedInUsername();
    cout << "Library Management System" << endl;
    cout <<"Login:"<< Loginname << endl;
    cout << "1. Login" << endl;
    cout << "2. Logout" << endl;
    cout << "3. Register" << endl;
    cout << "4. Add Book" << endl;
    cout << "Select an option: ";
    cin >> i;
   switch (i)
   {  
    //登录  
    case 1: 
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            sys.UserLogin(username, password);
            break;
        }
    //退出登录
    case 2:
        {
            string username = Loginname;
            sys.UserLogout(username);
            cout <<"User " << username << " logged out successfully." << endl;
            break;
        }
    //注册
    case 3:
        {
            string username, password;
            cout << "Enter new username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            User newUser(username, password);
            sys.addUser(newUser);
            cout << "User " << username << " registered successfully." << endl;
            break;
        }
    //添加图书
    case 4:
        {
            string isbn, title, author;
            cout << "Enter ISBN: ";
            cin >> isbn;
            cout << "Enter Title: ";
            cin >> title;
            cout << "Enter Author: ";
            cin >> author;
            Book newBook(isbn, title, author);
            sys.addBook(newBook);
            cout << "Book " << title << " added successfully." << endl;
            break;
        }
    //退出系统
    case 0:
        {
            sys.SaveData();
            cout << "Exiting system. Goodbye!" << endl;
            return 0;
        }
   }
   }
    return 0;
}