#pragma once
#include "Frame.h"
#include "StartFillWhenFrame.h"
#include "SensorHeightFrame.h"

class TankStatusFrame : public Frame
{
private:
    /* data */
public:
    TankStatusFrame(SH1106 *oled, FrameManager *frameManager);
    ~TankStatusFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
