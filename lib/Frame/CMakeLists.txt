cmake_minimum_required(VERSION 3.5)

project(FRAME)

add_library(FRAME STATIC
    Frame.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(FRAME pico_stdlib)
target_include_directories(FRAME PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
