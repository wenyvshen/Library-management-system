#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <Windows.h>

// 程序入口：负责菜单循环与用户交互
int main()
{
    // 设置控制台为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, ".UTF-8");

    System sys;
    sys.LoadData();
   int i;
   while (1)
   {
    string Loginname = sys.getLoggedInUsername();
    cout << "图书管理系统" << endl;
    cout << "当前登录用户：" << Loginname << endl;
    cout << "1. 登录" << endl;
    cout << "2. 登出" << endl;
    cout << "3. 注册" << endl;
    cout << "4. 添加图书" << endl;
    cout << "5. 显示全部图书" << endl;
    cout << "6. 搜索图书" << endl;
    cout << "7. 借阅图书" << endl;
    cout << "0. 退出" << endl;
    cout << "请选择功能：";
    cin >> i;
   switch (i)
   {  
    //登录  
    case 1: 
        {
            string username, password;
            cout << "请输入用户名：";
            cin >> username;
            cout << "请输入密码：";
            cin >> password;
            sys.UserLogin(username, password);
            break;
        }
    //退出登录
    case 2:
        {
            string username = Loginname;
            sys.UserLogout(username);
            cout << "用户 " << username << " 已退出登录。" << endl;
            break;
        }
    //注册
    case 3:
        {
            string username, password;
            cout << "请输入新用户名：";
            cin >> username;
            cout << "请输入新密码：";
            cin >> password;
            User newUser(username, password);
            sys.addUser(newUser);
            cout << "用户 " << username << " 注册成功。" << endl;
            break;
        }
    //添加图书
    case 4:
        {
            string isbn, title, author;
            int quantity;
            cout << "请输入 ISBN：";
            cin >> isbn;
            cout << "请输入书名：";
            cin >> title;
            cout << "请输入作者：";
            cin >> author;
            cout << "请输入数量：";
            cin >> quantity;
            Book newBook(isbn, title, author, quantity);
            sys.addBook(newBook);
            cout << "图书《" << title << "》添加成功。" << endl;
            break;
        }
    //显示全部图书
    case 5:
        {
            sys.displayAllBooks();
            break;
        }
    //搜索图书
    case 6:
        {
            int mode = 0;
            cout << "请选择查询方式（1-按书名关键词，2-按作者）：";
            cin >> mode;
            cin.ignore(); // 清除换行符
            bool found = false;
            if (mode == 1) {
                string keyword;
                cout << "请输入书名关键词：";
                getline(cin, keyword);
                auto matches = sys.searchBooksByTitleKeyword(keyword);
                for (const auto& book : matches) {
                    book.displayInfo();
                    found = true;
                }
                if (!found) {
                    cout << "未找到包含关键词 '" << keyword << "' 的图书。" << endl;
                }
            } else if (mode == 2) {
                string author;
                cout << "请输入作者名：";
                getline(cin, author);
                auto matches = sys.searchBooksByAuthor(author);
                for (const auto& book : matches) {
                    book.displayInfo();
                    found = true;
                }
                if (!found) {
                    cout << "未找到作者为 '" << author << "' 的图书。" << endl;
                }
            } else {
                cout << "无效的查询方式！" << endl;
            }
            break;
        }
    //借阅图书
    case 7:
        {
            if(Loginname=="")
            {
                cout<<"请先登录"<<endl;
                break;
            }
            else
            {
            cout << "请输入你要借阅图书的ISBN码" <<endl;
            string isbn;
            cin >> isbn;
            sys.borrowBook(Loginname, isbn);
            break;
            }
        }
    //查看当前用户借阅记录(若管理员则查看所有，暂未实现管理员账号)
    case 8:
        {
            if(Loginname=="")
            {
                cout<<"请先登录"<<endl;
                break;
            }
            else
            {
                cout << "用户名          书籍名" << endl;
                const auto& users = sys.getUsers();
                for (const auto& user : users) {
                    if (user.getName() == Loginname) {
                        for (int i = 0; i < 100; ++i) {
                            string entry = user.getHistoryEntry(i);
                            if (!entry.empty()) {
                                cout << user.getName() << "          " << entry << endl;
                            }
                        }
                        break;
                    }
                }
            }
        }
    //退出系统
    case 0:
        {
            sys.SaveData();
            cout << "正在退出系统，感谢使用！" << endl;
            return 0;
        }
   }
   }
    return 0;
}