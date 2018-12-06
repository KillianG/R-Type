cmake_minimum_required(VERSION 3.7)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
		message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(R-Type)
execute_process(COMMAND git submodule update --init --recursive)

ENABLE_TESTING()

include(CMakeSources.cmake)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/SFML)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs)
add_subdirectory(${CMAKE_SOURCE_DIR}/Server/Monsters)

link_directories(
		${CMAKE_SOURCE_DIR}/build/lib
		${CMAKE_SOURCE_DIR}/libs/SFML
)

include_directories(
		${PROJECT_SOURCE_DIR}/libs/LOG
		${PROJECT_SOURCE_DIR}/libs/Network
		${PROJECT_SOURCE_DIR}/libs/EventManager
		${PROJECT_SOURCE_DIR}/libs/Exception
		${PROJECT_SOURCE_DIR}/libs/Logger
		${PROJECT_SOURCE_DIR}/includes
		${PROJECT_SOURCE_DIR}/libs
)


#Final executable
add_executable(RTypeClient Client/main.cpp ${CLIENT_SRCS} Client/OptionsMenu/OptionsMenu.cpp Client/OptionsMenu/OptionsMenu.hpp)
add_executable(RTypeServer Server/main.cpp ${SERVER_SRCS})
add_executable(SettingsTest Client/test/test.cpp Client/MainMenu/Settings.hpp)
add_executable(ClientTest Client/test/test.cpp ${CLIENT_SRCS})
add_executable(ServerTest Server/test/test.cpp ${SERVER_SRCS} Server/test/gameCoreTest.cpp Server/test/testParsingLevel.cpp)

add_test(NAME SettingsTest COMMAND SettingsTest)
add_test(NAME ClientTest COMMAND ClientTest)
add_test(NAME ServerTest COMMAND ServerTest)

target_include_directories(ClientTest PRIVATE
		${PROJECT_SOURCE_DIR}/libs/SFML/include
		${PROJECT_SOURCE_DIR}/libs/GFX
		${PROJECT_SOURCE_DIR}/Server/includes
		)

target_include_directories(ServerTest PRIVATE
		${PROJECT_SOURCE_DIR}/libs/ECS
		${PROJECT_SOURCE_DIR}/libs/EventManager
		${PROJECT_SOURCE_DIR}/Server/includes)

target_include_directories(RTypeClient PRIVATE
		${PROJECT_SOURCE_DIR}/Client/includes
		${PROJECT_SOURCE_DIR}/libs/SFML/include
		${PROJECT_SOURCE_DIR}/libs/GFX
		)

target_include_directories(RTypeServer PRIVATE
		${PROJECT_SOURCE_DIR}/libs/ECS
		${PROJECT_SOURCE_DIR}/Server/includes
		)


target_link_libraries(ClientTest PRIVATE GFX Logger Exception pthread network boost_system sfml-audio sfml-system sfml-graphics sfml-window)
target_link_libraries(RTypeClient PRIVATE GFX Logger Exception pthread network boost_system sfml-audio sfml-system sfml-graphics sfml-window)
target_link_libraries(ServerTest PRIVATE ECS Logger network pthread Logger Exception boost_filesystem boost_system dl -lstdc++fs)
target_link_libraries(RTypeServer PRIVATE ECS Logger network pthread Logger Exception boost_filesystem boost_system dl -lstdc++fs)

target_compile_options(RTypeServer PRIVATE -Wall)
target_compile_options(RTypeClient PRIVATE -Wall -fPIC)
