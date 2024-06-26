#pragma once
#include "Frame.h"
#include "WaterDepthFrame.h"
#include "StartFillWhenFrame.h"

class StopFillWhenFrame : public Frame
{
private:
    /* data */
public:
    StopFillWhenFrame(SH1106 *oled, FrameManager *frameManager);
    ~StopFillWhenFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
