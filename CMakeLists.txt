cmake_minimum_required(VERSION 3.15)
project(backtracking)

set(CMAKE_CXX_STANDARD 17)

add_executable(backtracking main.cpp Backtracker.hpp)

target_link_libraries(backtracking)