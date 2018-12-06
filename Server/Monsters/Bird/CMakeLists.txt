cmake_minimum_required(VERSION 3.4)

project(_bird)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Monsters)

add_library(${PROJECT_NAME} SHARED Bird.cpp)
add_library(${PROJECT_NAME}2 SHARED Bird2.cpp)
add_library(${PROJECT_NAME}3 SHARED Bird3.cpp)