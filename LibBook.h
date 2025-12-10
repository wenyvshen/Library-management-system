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
    void saveToFile() const;
    void loadFromFile();  

private:
    string isbn;          // ISBN码
    string title;         // 标题
    string author;        // 作者
};

#endif