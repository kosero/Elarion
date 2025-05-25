cmake_minimum_required(VERSION 3.16)
project(Elarion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(inc)

file(GLOB_RECURSE SOURCES src/*.cxx)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_compile_options(
    -Wall
    -Wextra
    -pedantic
    -O3
    -Wconversion
    -Wnull-dereference
    -pipe
    -fno-common
    -fstack-protector-strong
)

add_executable(Elarion ${SOURCES})

target_link_libraries(Elarion
    raylib
    m
    dl
    pthread
    GL
    enet
)
