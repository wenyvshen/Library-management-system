#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <Windows.h>
#include <ctime>

using namespace std;

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
        cout << "当前登录用户：" << (Loginname.empty() ? "未登录" : Loginname) << endl;
        cout << "1. 登录" << endl;
        cout << "2. 登出" << endl;
        cout << "3. 注册" << endl;
        cout << "4. 添加图书" << endl;
        cout << "5. 显示全部图书" << endl;
        cout << "6. 搜索图书" << endl;
        cout << "7. 借阅图书" << endl;
        cout << "8. 查看借阅记录" << endl;
        cout << "9. 归还图书" << endl;
        cout << "10. 续借图书" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择功能：";
        cin >> i;
        switch (i)
        {  
        case 1: // 登录
            {
                string username, password;
                cout << "请输入用户名：";
                cin >> username;
                cout << "请输入密码：";
                cin >> password;
                sys.UserLogin(username, password);
                break;
            }
        case 2: // 登出
            {
                if (Loginname.empty()) {
                    cout << "当前未登录。" << endl;
                } else {
                    sys.UserLogout(Loginname);
                }
                break;
            }
        case 3: // 注册
            {
                string username, password;
                int type;
                cout << "请输入新用户名：";
                cin >> username;
                cout << "请输入新密码：";
                cin >> password;
                cout << "请选择用户类型 (1-学生, 2-教师): ";
                cin >> type;
                
                User* newUser = nullptr;
                if (type == 1) {
                    newUser = new Student(username, password);
                } else if (type == 2) {
                    newUser = new Teacher(username, password);
                } else {
                    cout << "无效的用户类型。" << endl;
                    break;
                }
                
                sys.addUser(newUser);
                cout << "用户 " << username << " 注册成功。" << endl;
                break;
            }
        case 4: // 添加图书
            {
                string isbn, title, author;
                int quantity;
                int isSpecialInt;
                cout << "请输入 ISBN：";
                cin >> isbn;
                cout << "请输入书名：";
                cin >> title;
                cout << "请输入作者：";
                cin >> author;
                cout << "请输入数量：";
                cin >> quantity;
                cout << "是否为特殊图书 (1-是, 0-否): ";
                cin >> isSpecialInt;
                
                Book newBook(isbn, title, author, quantity, isSpecialInt == 1);
                sys.addBook(newBook);
                cout << "图书《" << title << "》添加成功。" << endl;
                break;
            }
        case 5: // 显示全部图书
            {
                sys.displayAllBooks();
                break;
            }
        case 6: // 搜索图书
            {
                int mode = 0;
                cout << "请选择查询方式（1-按书名关键词，2-按作者）：";
                cin >> mode;
                cin.ignore(); 
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
        case 7: // 借阅图书
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
        case 8: // 查看当前用户借阅记录
            {
                if(Loginname=="")
                {
                    cout<<"请先登录"<<endl;
                    break;
                }
                else
                {
                    const auto& users = sys.getUsers();
                    for (const auto* user : users) {
                        if (user->getName() == Loginname) {
                            const auto& history = user->getHistory();
                            if (history.empty()) {
                                cout << "无借阅记录。" << endl;
                            } else {
                                cout << "ISBN\t\t\t借阅时间\t\t\t续借次数" << endl;
                                for (const auto& rec : history) {
                                    char buffer[26];
                                    ctime_s(buffer, sizeof(buffer), &rec.borrowDate);
                                    // 去掉换行符
                                    string timeStr(buffer);
                                    if (!timeStr.empty() && timeStr.back() == '\n') timeStr.pop_back();
                                    
                                    cout << rec.isbn << "\t" << timeStr << "\t" << rec.renewCount << endl;
                                }
                            }
                            break;
                        }
                    }
                    break; 
                }
            }
        case 9: // 归还图书
            {
                if(Loginname=="")
                {
                    cout<<"请先登录"<<endl;
                    break;
                }
                else
                {
                    string isbn;
                    cout << "请输入你要归还图书的ISBN码" <<endl;
                    cin >> isbn;
                    sys.returnBook(Loginname, isbn);
                    break;
                }
            }
        case 10: // 续借图书
            {
                if(Loginname=="")
                {
                    cout<<"请先登录"<<endl;
                    break;
                }
                else
                {
                    string isbn;
                    cout << "请输入你要续借图书的ISBN码" <<endl;
                    cin >> isbn;
                    sys.renewBook(Loginname, isbn);
                    break;
                }
            }
        case 0: // 退出
            {
                sys.SaveData();
                cout << "正在退出系统，感谢使用！" << endl;
                return 0;
            }
        default:
            cout << "无效的选择，请重试。" << endl;
        }
    }
    return 0;
}