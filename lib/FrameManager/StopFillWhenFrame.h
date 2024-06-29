#pragma once
#include "Frame.h"
#include "WaterDepthFrame.h"
#include "StartFillWhenFrame.h"

class StopFillWhenFrame : public Frame
{
private:
    /* data */
    const uint16_t step = 5;
    uint16_t startFillWhenValue = 0;

public:
    StopFillWhenFrame(SH1106 *oled, FrameManager *frameManager);
    ~StopFillWhenFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
