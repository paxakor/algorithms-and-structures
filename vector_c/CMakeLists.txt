cmake_minimum_required(VERSION 3.0)
project(vector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

include_directories("sources/")

set(SOURCES
    sources/vector.c
    main.c)

set(HEADERS
    sources/vector.h)

add_executable(vector ${SOURCES})
