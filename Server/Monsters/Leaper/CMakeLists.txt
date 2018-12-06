cmake_minimum_required(VERSION 3.4)

project(_leaper)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Monsters)

add_library(${PROJECT_NAME} SHARED Leaper.cpp LeaperExtern.cpp)
add_library(${PROJECT_NAME}2 SHARED Leaper2.cpp Leaper.cpp)