cmake_minimum_required(VERSION 3.27)
project(cmake)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake
        data/input.txt
        src/bdominiq.cpp)

add_executable(bdominiq src/bdominiq.cpp)
add_executable(output data/output.txt)
add_executable(CMakeLists CMakeLists.txt)