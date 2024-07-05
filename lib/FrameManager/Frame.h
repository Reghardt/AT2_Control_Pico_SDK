#pragma once
#include "SH1106.h"
#include "FrameManager.h"
#include "TankCFG.h"
#include <string>

class FrameManager;

class Frame
{
private:
public:
    Frame(SH1106 *oled, FrameManager *frameManager);
    ~Frame();

    virtual void render() = 0;

    virtual void button0() = 0;
    virtual void button1() = 0;
    virtual void button2() = 0;
    virtual void button3() = 0;

    // virtual void update();

protected:
    SH1106 *oled;
    FrameManager *frameManager;

    void navControls();
    void editControls();

    bool editMode = false;
    uint16_t tempValue = 0;
};
