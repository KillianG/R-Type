cmake_minimum_required(VERSION 3.7)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
    message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(RType_libs)

set(CMAKE_CXX_STANDARD 14)

add_library(ECS SHARED ECS/Entity.cpp ECS/Entity.hpp)

link_directories(${CMAKE_SOURCE_DIR}/../build/lib)

target_link_libraries(ECS PRIVATE)

target_link_libraries(ECS PRIVATE)
target_include_directories(ECS PRIVATE)

target_compile_options(ECS PRIVATE -Wall -Werror -g3)
