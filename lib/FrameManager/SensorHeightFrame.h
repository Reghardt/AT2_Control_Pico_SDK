#pragma once
#include "Frame.h"
#include "TankRadiusFrame.h"
#include "WaterDepthFrame.h"

class SensorHeightFrame : public Frame
{
private:
    const uint16_t step = 5;
    uint16_t waterDepthValue = 0;

public:
    SensorHeightFrame(SH1106 *oled, FrameManager *frameManager);
    ~SensorHeightFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
