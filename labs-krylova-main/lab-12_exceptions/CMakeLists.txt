cmake_minimum_required(VERSION 3.16)
project(lab-12_exceptions CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-12_exceptions
        include/matrix.h
        src/matrix.cpp
        src/main.cpp
        )

target_include_directories(lab-12_exceptions PUBLIC ./include)