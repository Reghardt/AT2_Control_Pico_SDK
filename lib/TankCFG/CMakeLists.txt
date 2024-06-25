cmake_minimum_required(VERSION 3.13)

project(TankCFG)


add_library(TankCFG STATIC
    TankCFG.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(TankCFG pico_stdlib PLFS nlohmann_json)
target_include_directories(TankCFG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
