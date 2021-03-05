cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER clang)

add_definitions(-std=gnu++17)

project(DLA-Single)

add_executable(DLA-Single main.cpp randomGenerator.h)
#target_include_directories(DLA-Single PRIVATE include)
include_directories(include)
#target_link_libraries(DLA-Single cxxopts)
