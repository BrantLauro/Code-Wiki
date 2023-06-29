cmake_minimum_required(VERSION 3.24)
project(Code_Wiki C)

set(CMAKE_C_STANDARD 99)

add_executable(Code_Wiki main.c interface.c interface.h dados.c dados.h)
