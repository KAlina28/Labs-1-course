cmake_minimum_required(VERSION 3.16)
project(lab-03_..mergesort C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-03_mergesort
        src/main.c
        src/mergesort.c
        include/mergesort.h
        )

target_include_directories(lab-03_mergesort PUBLIC ./include)

