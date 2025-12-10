#include "LibBook.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// 构造函数实现
Book::Book(string isbn, string title, string author)
    : isbn(isbn), title(title), author(author){}

void Book::displayInfo() const
{
    cout << "ISBN: " << isbn << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
}

void Book::saveToFile() const
{
    char t_isbn[20];
    char t_title[100];
    char t_author[50];
    strcpy(t_isbn,isbn.c_str());
    strcpy(t_title,title.c_str());
    strcpy(t_author,author.c_str());

    fstream file;
    file.open(R"(F:\library\Library-management-system\Book.dat)", ios::app | ios::binary);
    if (file.is_open() == false)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.write((const char*)t_isbn, sizeof(t_isbn));
    file.write((const char*)t_title, sizeof(t_title));
    file.write((const char*)t_author, sizeof(t_author));
    file.close();
}

void Book::loadFromFile()
{
    char t_isbn[20];
    char t_title[100];
    char t_author[50];

    fstream file;
    file.open(R"(F:\library\Library-management-system\Book.dat)", ios::in | ios::binary);
    if (file.is_open() == false)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file.read(t_isbn, sizeof(t_isbn));
    file.read(t_title, sizeof(t_title));
    file.read(t_author, sizeof(t_author));
    file.close();

    isbn = string(t_isbn);
    title = string(t_title);
    author = string(t_author);
}; 