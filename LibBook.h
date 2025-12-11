#ifndef LIBBOOK_H
#define LIBBOOK_H

#include <string>
using std::string;

class Book
{
public:
    // 默认构造：生成空书籍
    Book() = default;
    // 构造：设置书籍基本信息与库存
    Book(string isbn, string title, string author, int quantity = 0);
    
    // 展示书籍信息
    void displayInfo() const;
    // 设置库存数量
    void setQuantity(int qty);
    // 获取 ISBN
    string getIsbn() const;
    // 获取书名
    string getTitle() const;
    // 获取作者
    string getAuthor() const;
    // 获取库存数量
    int getQuantity() const;

private:
    string isbn;          // ISBN码
    string title;         // 标题
    string author;        // 作者
    int quantity;      // 数量
};

#endif