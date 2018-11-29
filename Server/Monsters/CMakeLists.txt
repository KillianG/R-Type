cmake_minimum_required(VERSION 3.4)

project(Monsters)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-W -Wall")

include_directories(
  includes/
)

add_subdirectory(Bird)
add_subdirectory(Bird2)
add_subdirectory(FirstBoss)

