cmake_minimum_required(VERSION 3.17)
project(prog3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Werror")

add_executable(prog3 main.c csv.c Butterfly.c Photo.c)

