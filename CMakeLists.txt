cmake_minimum_required(VERSION 3.16)
project(Elarion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cxx)

add_executable(Elarion ${SOURCES})

target_compile_options(Elarion PRIVATE
        -Wall -Wextra -pedantic -Wconversion -Wnull-dereference
        -pipe -fno-common -fstack-protector-strong
)

set(BUILD_SHARED_LIBS OFF)
find_package(raylib REQUIRED)

target_link_libraries(Elarion PRIVATE
        /usr/local/lib/libraylib.a
        m dl pthread GL enet
)

target_include_directories(Elarion PRIVATE inc /usr/local/include)
