#include "LibBook.h"
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

// 构造函数实现
Book::Book(string isbn, string title, string author)
    : isbn(isbn), title(title), author(author), StorageAddress(0) {}

void Book::displayInfo() const
{
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Storage Address: " << StorageAddress << endl;
}

void Book::setStorageAddress(int address)
{
    StorageAddress = address;
}

int Book::getStorageAddress() const
{
    return StorageAddress;
}