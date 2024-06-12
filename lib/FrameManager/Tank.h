#pragma once
#include "Frame.h"
#include "FillWhen.h"

class Tank : public Frame
{
private:
    /* data */
public:
    Tank(SH1106 *oled, FrameManager *frameManager);
    ~Tank();

    void render();

    void button0();
    void button1();
    void button2();
    void button3();
};
