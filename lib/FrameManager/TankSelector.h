#pragma once
#include "Frame.h"
#include "FillWhen.h"

class TankSelector : public Frame
{
private:
    /* data */
public:
    TankSelector(SH1106 *oled, FrameManager *frameManager);
    ~TankSelector();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};