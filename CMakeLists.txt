cmake_minimum_required(VERSION 3.6)
project(P5ED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Abb.h)
add_executable(untitled ${SOURCE_FILES})