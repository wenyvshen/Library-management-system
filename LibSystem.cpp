#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;

void System::addBook(const Book& book)
{
    books.push_back(book);
}

void System::displayAllBooks() const
{
    for (const auto& book : books)
    {
        book.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}

void System::addUser(const User& user)
{
    users.push_back(user);
}

void System::displayAllUsers() const
{
    for (const auto& user : users)
    {
        user.displayInfo();
        std::cout << "------------------" << std::endl;
    }
}