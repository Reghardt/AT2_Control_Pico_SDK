#pragma once
#include "Frame.h"
#include "TankStatusFrame.h"
#include "WaterDepthFrame.h"

class SensorHeightFrame : public Frame
{
private:
    /* data */
public:
    SensorHeightFrame(SH1106 *oled, FrameManager *frameManager);
    ~SensorHeightFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
