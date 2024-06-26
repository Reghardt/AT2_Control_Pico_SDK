#pragma once
#include "Frame.h"
#include "SensorHeightFrame.h"
#include "StopFillWhenFrame.h"

class WaterDepthFrame : public Frame
{
private:
    /* data */
public:
    WaterDepthFrame(SH1106 *oled, FrameManager *frameManager);
    ~WaterDepthFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
