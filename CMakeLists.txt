cmake_minimum_required(VERSION 3.10)

project(LibraryManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    Libraryv2.0.cpp
    LibBook.cpp
    LibSystem.cpp
    LibUser.cpp
)