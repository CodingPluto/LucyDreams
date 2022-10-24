cmake_minimum_required(VERSION 3.10)
project(GameData)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(GameData
Game.h
GameObject.h
Sprite.h
Game.cpp
GameObject.cpp
Sprite.cpp
)