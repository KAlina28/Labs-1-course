cmake_minimum_required(VERSION 3.16)
project(lab-10_cppio CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-10_cppio
        src/main.cpp
        src/employees.cpp
        src/bin_manip.cpp
        include/employees.h
        include/bin_manip.h
        )

target_include_directories(lab-10_cppio PUBLIC ./include)
