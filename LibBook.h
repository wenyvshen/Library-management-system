#ifndef LIBBOOK_H
#define LIBBOOK_H

#include <string>
using std::string;

class Book
{
public:
    Book() = default;
    Book(string isbn, string title, string author);
    
    void displayInfo() const;
    void setStorageAddress(int address);
    int getStorageAddress() const;

private:
    string isbn;          // ISBN码
    string title;         // 标题
    string author;        // 作者
    int StorageAddress;   // 存储地址
};

#endif