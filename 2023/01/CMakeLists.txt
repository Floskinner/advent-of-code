cmake_minimum_required(VERSION 3.12.4)
set(CMAKE_CXX_STANDARD 20)

project(AdventOfCode-01)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

enable_testing()
