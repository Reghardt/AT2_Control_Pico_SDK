cmake_minimum_required(VERSION 3.13)

project(TankState)


add_library(TankState STATIC
    TankState.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(TankState pico_stdlib TankCFG)
target_include_directories(TankState PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
