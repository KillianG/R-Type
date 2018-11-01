cmake_minimum_required(VERSION 3.7)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
		message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(R-Type)

ENABLE_TESTING()

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

link_directories(${CMAKE_SOURCE_DIR}/build/lib)

add_subdirectory(libs)

# General SRCS
set(CLIENT_SRCS Client/base.cpp)
set(SERVER_SRCS Serveur/base.cpp)

#Final executable
add_executable(RTypeClient Client/main.cpp ${CLIENT_SRCS})
add_executable(RTypeServer Serveur/main.cpp ${SERVER_SRCS})

add_executable(ClientTest Client/test/test.cpp ${CLIENT_SRCS})
add_test(NAME ClientTest COMMAND ClientTest)
add_executable(ServerTest Serveur/test/test.cpp ${SERVER_SRCS})
add_test(NAME ServerTest COMMAND ServerTest)

target_include_directories(ClientTest PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Server/includes)

target_include_directories(ServerTest PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Server/includes)

target_include_directories(RTypeClient PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Client/includes)

target_link_libraries(RTypeClient PRIVATE)
target_compile_options(RTypeClient PRIVATE -Wall -Werror -fPIC -g3)

target_include_directories(RTypeServer PRIVATE
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/Server/includes)

target_link_libraries(RTypeServer PRIVATE)
target_compile_options(RTypeServer PRIVATE -Wall -Werror -g3)
