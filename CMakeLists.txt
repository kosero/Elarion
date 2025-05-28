cmake_minimum_required(VERSION 3.16)
project(Elarion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

file(GLOB_RECURSE SOURCES src/*.cxx)
file(GLOB_RECURSE HEADERS inc/*.hxx)

add_executable(Elarion ${SOURCES} ${HEADERS})

target_include_directories(Elarion PRIVATE inc /usr/local/include)

target_compile_options(Elarion PRIVATE
    -Wall -Wextra -pedantic -Wconversion -Wnull-dereference
    -pipe -fno-common -fstack-protector-strong
)

target_link_libraries(Elarion PRIVATE
    /usr/local/lib/libraylib.a
    m dl pthread GL enet
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

