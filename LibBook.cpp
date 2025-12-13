#include "LibBook.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// 构造：初始化基本信息与库存
Book::Book(string isbn, string title, string author, int quantity, bool isSpecial)
    : isbn(isbn), title(title), author(author), quantity(quantity), isSpecial(isSpecial) {}

// 打印图书基本信息
void Book::displayInfo() const
{
    cout << "ISBN：" << isbn << endl;
    cout << "书名：" << title << endl;
    cout << "作者：" << author << endl;
    cout << "数量：" << quantity << endl;
    cout << "类型：" << (isSpecial ? "特殊图书" : "普通图书") << endl;
}

// 更新库存数量
void Book::setQuantity(int qty)
{
    quantity = qty;
}

// 返回 ISBN
string Book::getIsbn() const
{
    return isbn;
}

// 返回书名
string Book::getTitle() const
{
    return title;
}

// 返回作者
string Book::getAuthor() const  
{
    return author;
}

// 返回库存数量
int Book::getQuantity() const
{
    return quantity;
}

// 返回是否为特殊图书
bool Book::getIsSpecial() const
{
    return isSpecial;
}