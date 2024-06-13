cmake_minimum_required(VERSION 3.16)

project(
    example
    VERSION 1.0
    LANGUAGES CXX
)

add_library(mylib mylib.cpp mylib.hpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE mylib)
