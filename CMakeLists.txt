cmake_minimum_required(VERSION 3.23)
project(mcode)

set(CMAKE_CXX_STANDARD 17)

add_executable(mcode src/mcode.cpp src/algs/rle.cpp src/algs/rle.h)
