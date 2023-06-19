cmake_minimum_required(VERSION 3.25)
project(max_flow)

set(CMAKE_CXX_STANDARD 17)

add_executable(max_flow main.cpp Hypercube.cpp Hypercube.h Edge.cpp Edge.h utils.h)
