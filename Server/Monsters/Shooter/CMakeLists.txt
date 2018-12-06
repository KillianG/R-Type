cmake_minimum_required(VERSION 3.4)

project(_shooter)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Monsters)

add_library(${PROJECT_NAME} SHARED Shooter.cpp)