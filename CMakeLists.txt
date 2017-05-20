cmake_minimum_required(VERSION 3.7)
project(HW3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        defs.h
        list.h
        list.c
        person.h)

add_executable(HW3 ${SOURCE_FILES})