cmake_minimum_required(VERSION 3.13)
project(Fibo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Fibo fibo.cc fibo.h main.cpp)