cmake_minimum_required(VERSION 3.6)
project(astar)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES astar.c astar.h list.h list.c path_finder.c)
add_executable(pathfinder ${SOURCE_FILES})