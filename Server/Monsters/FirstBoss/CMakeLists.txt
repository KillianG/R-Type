cmake_minimum_required(VERSION 3.4)

project(_FirstBoss)

add_library(${PROJECT_NAME} SHARED FirsBoss.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Monsters)
