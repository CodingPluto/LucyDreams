cmake_minimum_required(VERSION 3.10)
project(Colliders)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Colliders
    PlatformerCollision.h
    Collider.h
    AABBCollider.h
    PlatformerCollision.cpp
    Collider.cpp
    AABBCollider.cpp
)