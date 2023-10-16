cmake_minimum_required(VERSION 3.17)
project(File_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(File_System main.cpp Wad.cpp Wad.h wadfs.cpp)