#pragma once
#include "Frame.h"
#include "TankStatusFrame.h"
#include "SensorHeightFrame.h"

class TankRadiusFrame : public Frame
{
private:
    const uint16_t step = 5;

public:
    TankRadiusFrame(SH1106 *oled, FrameManager *frameManager);
    ~TankRadiusFrame();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
