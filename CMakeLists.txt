cmake_minimum_required(VERSION 3.26)
project(Laboratory_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Laboratory_19
        main.c
        libs/files/files.c
        libs/files/files.h
        libs/tasks/tasks.h
        libs/tasks/tasks.c)
