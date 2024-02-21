cmake_minimum_required(VERSION 3.15...3.26)

project(
    MATRIX_MULTIPLY
    VERSION 1.0
    LANGUAGES CXX
)


# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(multiply main.cpp multiply.cpp timing.cpp)