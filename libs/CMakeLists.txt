cmake_minimum_required(VERSION 3.12)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
    message(FATAL_ERROR "You can't build in the root directory.")
endif()

project(babel_libs)

set(CMAKE_CXX_STANDARD 17)

add_library(babelOpus SHARED babelOpus/babelOpus.cpp babelOpus/babelOpus.hpp)

add_library(audioPort SHARED
        portAudio/AudioPort.cpp portAudio/AudioPort.hpp babelOpus/babelOpus.cpp babelOpus/babelOpus.hpp)

add_library(networkQt SHARED
        networkQt/QtProtocole.cpp networkQt/QtProtocole.hpp ../includes/SipHeader.cpp ../includes/SipHeader.hpp ../includes/NetworkException.hpp networkQt/MySocket.hpp)

add_library(networkBoost SHARED
        NetworkBoost/NetworkBoost.cpp NetworkBoost/NetworkBoost.hpp NetworkBoost/TcpConnection.cpp NetworkBoost/TcpConnection.hpp ../includes/SipHeader.cpp ../includes/SipHeader.hpp ../includes/ThreadContainer.hpp ../includes/NetworkException.hpp ../includes/BabelHeader.hpp)


link_directories(${CMAKE_SOURCE_DIR}/libconan
        ${CMAKE_SOURCE_DIR}/../build/lib)

target_link_libraries(networkBoost PRIVATE boost_system boost_thread)


target_link_libraries(audioPort PRIVATE portaudio rt m asound pthread jack babelOpus networkQt)
target_link_libraries(babelOpus PRIVATE opus)


include_directories(${PROJECT_SOURCE_DIR}/networkBoost
        ${PROJECT_SOURCE_DIR}/includeconan
        ${PROJECT_SOURCE_DIR}/../includes
        )

target_link_libraries(ECS PRIVATE Qt5Core)
target_include_directories(ECS PRIVATE
        )

target_compile_options(ECS PRIVATE -Wall -Werror -g3)
