#pragma once
#include "Frame.h"
#include "StopFillWhenFrame.h"
#include "TankStatusFrame.h"

class StartFillWhenFrame : public Frame
{
private:
    /* data */
public:
    StartFillWhenFrame(SH1106 *oled, FrameManager *frameManager);
    ~StartFillWhenFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};