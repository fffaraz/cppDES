cmake_minimum_required(VERSION 3.10)
project(cppDES)

set(CMAKE_CXX_STANDARD 11)

add_executable(cppDES main.cpp des.cpp des3.cpp descbc.cpp fileencryption.cpp)