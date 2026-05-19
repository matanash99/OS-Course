cmake_minimum_required(VERSION 3.10)
project(myshell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(myshell src/main.cpp)