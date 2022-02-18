cmake_minimum_required(VERSION 3.21)
project(Machine_Oriented_Programming C)

set(CMAKE_C_STANDARD 11)

include_directories(machineprog)

add_executable(sandbox
        sandbox.c
        machineprog/binary.h)
