cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(snake VERSION 1.0)

include_directories("bin/headers" "bin/sources" "engine/headers" "engine/sources")

#link sdl2 libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

set(SOURCES 
    engine/sources/WindowRendering.cpp
    engine/sources/LTimer.cpp
    engine/sources/Colliders.cpp
    bin/sources/Tile.cpp
    bin/sources/SnakeGame.cpp)

add_executable(snake.out main.cpp ${SOURCES})
target_link_libraries(snake.out SDL2::SDL2 SDL2_image SDL2_ttf)
