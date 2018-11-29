cmake_minimum_required(VERSION 3.4)

project(_bird2)

add_library(${PROJECT_NAME} SHARED Bird2.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Monsters)
