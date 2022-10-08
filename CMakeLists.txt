cmake_minimum_required(VERSION 3.10)

project(LucyDreams VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
include(FindPkgConfig)
pkg_search_module(SDL2 required SDL2)
pkg_search_module(SDL2IMAGE required SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF required SDL2_ttf>=2.0.0)
pkg_search_module(SDL2MIXER required SDL2_mixer>=2.0.0)

add_subdirectory(src/utils)
add_subdirectory(src/handlers)
add_subdirectory(src/components)
add_subdirectory(src/colliders)
add_executable(LucyDreams
    src/Game.cpp
    src/Game.h
    src/GameObject.cpp
    src/GameObject.h
    src/main.cpp
    src/Position.h
    src/Sprite.cpp
    src/Sprite.h
    src/Trigger.cpp
    src/Trigger.h
    #src/Lucy.h
    #src/Lucy.cpp
)
target_include_directories(LucyDreams PUBLIC
"${PROJECT_BINARY_DIR}"
)
target_include_directories(LucyDreams PUBLIC
"${PROJECT_SOURCE_DIR}"
)
target_link_libraries(LucyDreams ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
target_link_libraries(LucyDreams Utilities Handlers Components Colliders)
