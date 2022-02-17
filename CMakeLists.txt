cmake_minimum_required(VERSION 3.17)
project(MatrixCalculator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(matrix_math)

add_executable(MatrixCalculator main.cpp)
