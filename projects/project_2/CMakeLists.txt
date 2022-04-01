cmake_minimum_required(VERSION 3.21)
project(Machine_Oriented_Programming_Project_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Yukon
        yukon.c commands.h cli.h)
