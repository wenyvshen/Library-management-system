#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;
int main()
{
    System librarySystem;
    Book myBook;
    myBook.loadFromFile();
    librarySystem.addBook(myBook);
    librarySystem.displayAllBooks();
    User myUser;
    myUser.loadFromFile();
    librarySystem.addUser(myUser);
    librarySystem.displayAllUsers();
    return 0;
}