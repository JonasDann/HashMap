cmake_minimum_required(VERSION 3.6)
project(HashMap)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES Main.c HashMap.c HashMap.h LinkedList.c LinkedList.h)
add_executable(HashMap ${SOURCE_FILES})