#pragma once

#include "Frame.h"

#define BUTTON_0 9
#define BUTTON_1 8
#define BUTTON_2 7
#define BUTTON_3 6

class Frame;

class FrameManager
{
private:
    Frame *frame;
    uint32_t lastPress;
    SH1106 *oled;

    bool shouldUpdate = false;

public:
    FrameManager(SH1106 *oled);
    ~FrameManager();

    void begin();
    void setFrame(Frame *frame);
    void tick();
    void update();
};
