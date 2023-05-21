
cmake_minimum_required(VERSION 3.16)
project(lab-09_figures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")
add_executable(lab-09_figures
        src/main.cpp
        src/Circle.cpp
        src/Figure.cpp
        src/Rectangle.cpp
        src/Scheme.cpp
        include/Circle.hpp
        include/Figure.hpp
        include/Rectangle.hpp
        include/Scheme.hpp
        )

target_include_directories(lab-09_figures PUBLIC ./include)