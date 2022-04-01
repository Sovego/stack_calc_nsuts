cmake_minimum_required(VERSION 3.21)
project(untitled8 C)

set(CMAKE_C_STANDARD 23)
MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
add_executable(untitled8 main.c)
