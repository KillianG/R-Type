cmake_minimum_required(VERSION 3.12)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
		message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(Babel)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

link_directories(${CMAKE_SOURCE_DIR}/build/lib)

add_subdirectory(libs)

add_executable(BabelClient
		Client/main.cpp
		)

add_executable(BabelServer
		Server/main.cpp
		)

target_include_directories(BabelClient PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Client/includes)

target_link_libraries(BabelClient PRIVATE Qt5Core Qt5Network Qt5Widgets networkQt babelOpus audioPort)
target_compile_options(BabelClient PRIVATE -Wall -Werror -fPIC -g3)

target_include_directories(BabelServer PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Server/includes
		)

target_link_libraries(BabelServer PRIVATE rt m pthread jack boost_system networkBoost)
target_compile_options(BabelServer PRIVATE -Wall -Werror -g3)
