cmake_minimum_required(VERSION 3.10)
project(Utilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Utilities
Colour.h
utils.h
src/utils.cpp
)