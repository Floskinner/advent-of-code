cmake_minimum_required(VERSION 3.12.4)
set(CMAKE_CXX_STANDARD 20)

project(AdventOfCode-02)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     ${CMAKE_CURRENT_SOURCE_DIR}/test.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})