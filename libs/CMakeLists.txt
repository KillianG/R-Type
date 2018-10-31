cmake_minimum_required(VERSION 3.12)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
    message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(babel_libs)

set(CMAKE_CXX_STANDARD 17)

add_library(ECS SHARED ECS/Entity.cpp ECS/Entity.hpp)


link_directories(${CMAKE_SOURCE_DIR}/../build/lib)

target_link_libraries(ECS PRIVATE boost_system boost_thread)

include_directories(${PROJECT_SOURCE_DIR}/networkBoost
        ${PROJECT_SOURCE_DIR}/includeconan
        ${PROJECT_SOURCE_DIR}/../includes
        )

target_link_libraries(ECS PRIVATE Qt5Core)
target_include_directories(ECS PRIVATE
        )

target_compile_options(ECS PRIVATE -Wall -Werror -g3)
