cmake_minimum_required(VERSION 3.25)
project(max_matching)

set(CMAKE_CXX_STANDARD 20)

add_executable(max_matching main.cpp Edge.cpp Edge.h Graph.cpp Graph.h)
