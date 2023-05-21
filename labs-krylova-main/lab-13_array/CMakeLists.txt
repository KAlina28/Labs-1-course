cmake_minimum_required(VERSION 3.16)
project(lab-13_array CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-13_array
        include/my_array.h
        src/main.cpp
        )

target_include_directories(lab-13_array PUBLIC ./include)