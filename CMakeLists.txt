cmake_minimum_required(VERSION 3.13)

project(ai)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES . src/*.[ch]pp)

add_executable(goap_hunter ${SOURCES})

