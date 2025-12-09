#include <iostream>
#include "LibBook.h"
#include "LibSystem.h"
using namespace std;
int main()
{
    System librarySystem;
    Book myBook("978-3-16-148410-0", "C++ Programming", "John Doe");
    librarySystem.addBook(myBook);
    librarySystem.displayAllBooks();
    User myUser("Alice");
    librarySystem.addUser(myUser);
    librarySystem.displayAllUsers();
    return 0;
}