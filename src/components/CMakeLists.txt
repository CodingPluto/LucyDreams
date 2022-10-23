cmake_minimum_required(VERSION 3.10)
project(Components)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Components
AnimationComponent.h
Component.h
ImageComponent.h
src/AnimationComponent.cpp
src/Component.cpp
src/ImageComponent.cpp
)