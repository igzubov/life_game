cmake_minimum_required(VERSION 3.5)
project(life_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(life_game main.cpp world.cpp fileVisualizer.cpp fileVisualizer.h)