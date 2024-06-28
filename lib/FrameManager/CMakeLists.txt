cmake_minimum_required(VERSION 3.5)

project(FrameManager)

add_library(FrameManager STATIC
    FrameManager.cpp
    Frame.cpp
    TankStatusFrame.cpp
    StartFillWhenFrame.cpp
    StopFillWhenFrame.cpp
    WaterDepthFrame.cpp
    SensorHeightFrame.cpp
    TankSelector.cpp
)

# Inherit the include directories from the Pico SDK
target_link_libraries(FrameManager pico_stdlib SH110X TankCFG)
target_include_directories(FrameManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
