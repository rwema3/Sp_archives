cmake_minimum_required(VERSION 3.27)
project(bdominiq)

set(CMAKE_CXX_STANDARD 20)

add_executable(bdominiq main.cpp)

add_executable(main main.cpp)
add_executable(output cmake-build-debug/data/output.txt)