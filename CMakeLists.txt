cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Abb.h Commit.h fecha.cpp fecha.h Fichero.h Gitcode.cpp Gitcode.h ListaDEnlazada2.h vDinamico.h Lista.h)
add_executable(untitled ${SOURCE_FILES})