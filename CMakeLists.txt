cmake_minimum_required(VERSION 3.6)
project(astar)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES astar.c pathfinder.c astar.h list.h list.c)
add_executable(pathfinder ${SOURCE_FILES})