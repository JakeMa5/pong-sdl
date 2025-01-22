cmake_minimum_required(VERSION 3.10)

project(Pong)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

include_directories(include)

add_executable(Pong
    src/main.cpp
    src/game.cpp
    src/paddle.cpp
    src/ball.cpp
)

target_link_libraries(Pong PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_mixer::SDL2_mixer)