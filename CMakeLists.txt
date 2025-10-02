cmake_minimum_required(VERSION 4.0)
project(DDSA C)

set(CMAKE_C_STANDARD 11)

add_executable(DDSA 9.2-passbypionter.c
        9-Day/9.2-reference.c
        9-Day/9.3-DMM-Malloc.c)
