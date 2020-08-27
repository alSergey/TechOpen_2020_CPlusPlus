cmake_minimum_required(VERSION 3.13)
project(game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

include_directories(.)
add_subdirectory(server)
add_subdirectory(client)