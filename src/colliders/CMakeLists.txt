cmake_minimum_required(VERSION 3.10)
project(Colliders)

add_library(Colliders
    PlatformerCollision.h
    src/PlatformerCollision.cpp
    Collider.h
    AABBCollider.h
    src/Collider.cpp
    src/AABBCollider.cpp
)