cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

project(Calender_Generator VERSION 1.0)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)

