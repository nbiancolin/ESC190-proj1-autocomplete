cmake_minimum_required(VERSION 3.24)
project(ESC190_proj1_autocomplete C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ESC190_proj1_autocomplete
        autocomplete.c
        autocomplete.h
        main.c)
