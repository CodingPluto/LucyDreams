cmake_minimum_required(VERSION 3.10)
project(Handlers)


include(FindPkgConfig)
pkg_search_module(SDL2 required SDL2)
pkg_search_module(SDL2IMAGE required SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF required SDL2_ttf>=2.0.0)
pkg_search_module(SDL2MIXER required SDL2_mixer>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

add_library(Handlers
Camera.h
CameraHandler.h
DisplayHandler.h
EventsHandler.h
Handler.h
HandlerError.h
ImageHandler.h
WindowHandler.h
src/Camera.cpp
src/CameraHandler.cpp
src/DisplayHandler.cpp
src/EventCallback.cpp
src/EventCallback.h
src/EventsHandler.cpp
src/Handler.cpp
src/HandlerError.cpp
src/ImageHandler.cpp
src/WindowHandler.cpp
)
target_link_libraries(Handlers ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
