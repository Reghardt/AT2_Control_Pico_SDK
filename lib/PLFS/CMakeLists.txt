cmake_minimum_required(VERSION 3.13)

project(PLFS)


add_subdirectory(pico-filesystem)
add_library(PLFS STATIC
    PLFS.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(PLFS pico_stdlib flash_filesystem)
target_include_directories(PLFS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
