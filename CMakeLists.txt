cmake_minimum_required(VERSION 3.17)
project(ComplexNumbers)

set(CMAKE_CXX_STANDARD 17)

# add coverage
# https://plugins.jetbrains.com/plugin/11031-c-c--coverage
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    link_libraries(gcov)
endif ()

add_executable(ComplexNumbers rational_num.h complex_num.h main.cpp)