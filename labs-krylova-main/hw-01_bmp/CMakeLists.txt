cmake_minimum_required(VERSION 3.16)
project(hw-01_bmp C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(hw-01_bmp
        src/main.c
        src/bmp.c
        include/bmp.h
        )

target_include_directories(hw-01_bmp PUBLIC ./include)

