cmake_minimum_required(VERSION 3.13)

project(Radio)


add_library(Radio STATIC
    Radio.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(Radio pico_stdlib)
target_include_directories(Radio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
