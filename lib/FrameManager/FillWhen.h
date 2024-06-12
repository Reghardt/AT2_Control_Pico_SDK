#pragma once
#include "Frame.h"
#include "Tank.h"

class FillWhen : public Frame
{
private:
    /* data */
public:
    FillWhen(SH1106 *oled, FrameManager *frameManager);
    ~FillWhen();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};