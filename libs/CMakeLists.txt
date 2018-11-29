cmake_minimum_required(VERSION 3.7)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
    message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(RType_libs)

set(CMAKE_CXX_STANDARD 14)

include(CMakeSources.cmake)

link_directories(
        ${PROJECT_SOURCE_DIR}/build/lib
)

include_directories(
        ${CMAKE_SOURCE_DIR}/includes
)

add_library(GFX SHARED ${GFX_RESOURCES})
add_library(ECS SHARED ${ECS_RESOURCES})
add_library(Logger SHARED ${LOGGER_RESOURCES})
add_library(Exception SHARED ${EXCEPTION_RESOURCES})
add_library(EventManager SHARED ${EVT_RESOURCES})
add_library(network SHARED ${NETWORK_RESOURCES})

add_executable(GfxTest GFX/test/test.cpp)
add_executable(LoggerTest LOG/test/test.cpp)
add_executable(ExceptionTest Exception/test/test.cpp)
add_executable(EventTest EventManager/unit_tests/Tests.cpp)
add_executable(EcsTest ECS/tests/ComponentTest.cpp ECS/tests/SystemTest.cpp ECS/tests/ManagerTest.cpp)
add_executable(NetworkTest Network/tests/MyRfcTest.cpp Network/tests/UdpTest.cpp Network/tests/TcpTest.cpp Network/tests/MyRfcTestTcp.cpp)

target_link_libraries(Exception PRIVATE Logger)
target_link_libraries(network PRIVATE Logger Exception pthread boost_filesystem boost_system)
target_link_libraries(GFX PRIVATE -lstdc++fs sfml-graphics sfml-window sfml-system sfml-audio -lgcov Logger Exception EventManager)
target_link_libraries(EventManager PRIVATE -lgcov)

target_link_libraries(GfxTest PRIVATE GFX -lstdc++fs pthread sfml-audio Logger sfml-graphics EventManager)
target_link_libraries(LoggerTest PRIVATE Logger)
target_link_libraries(EcsTest PRIVATE ECS pthread)
target_link_libraries(NetworkTest PRIVATE network pthread Logger Exception boost_filesystem boost_system)
target_link_libraries(ExceptionTest PRIVATE Exception)

#add_test(NAME GfxTest COMMAND GfxTest)
add_test(NAME EventTest COMMAND EventTest)
add_test(NAME LoggerTest COMMAND LoggerTest)
add_test(NAME EcsTest COMMAND EcsTest)
add_test(NAME NetworkTest COMMAND NetworkTest)
add_test(NAME ExceptionTest COMMAND ExceptionTest)

target_include_directories(GfxTest PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/GFX
        ${CMAKE_SOURCE_DIR}/libs/SFML/include)

target_include_directories(EventTest PRIVATE ${CMAKE_SOURCE_DIR}/../includes
        ${CMAKE_SOURCE_DIR}/libs/EventManager
        )

target_include_directories(LoggerTest PRIVATE ${CMAKE_SOURCE_DIR}/../includes
        ${CMAKE_SOURCE_DIR}/libs/LOG
        )

target_include_directories(EcsTest PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/ECS
        ${CMAKE_SOURCE_DIR}/SFML/include
        ${CMAKE_SOURCE_DIR}/libs/SFML/include
        )

target_include_directories(network PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}/libs/Network
        )

target_include_directories(NetworkTest PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}/libs/Network
        )

target_include_directories(ExceptionTest PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/Exception
        )

target_include_directories(GFX PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/SFML/include
        )

target_compile_options(ECS PRIVATE -Wall)
target_compile_options(network PRIVATE -Wall -g3)
target_compile_options(NetworkTest PRIVATE -Wall -g3)
target_compile_options(GFX PRIVATE -Wall --coverage)
target_compile_options(EventManager PRIVATE -Wall -Wextra --coverage)
target_compile_options(Logger PRIVATE -Wall)
target_compile_options(GfxTest PRIVATE -Wall)
