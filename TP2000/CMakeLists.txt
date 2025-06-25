cmake_minimum_required(VERSION 3.10)

project(TP2000)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(TP2000
    src/main.cpp
)

target_compile_options(TP2000
    -g
)