#include <iostream>
#include "LibBook.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
int main()
{
    Book book1("978-3-16-148410-0", "C++ Programming", "John Doe");
    book1.displayInfo();
    return 0;
}