#include "StopFillWhenFrame.h"

StopFillWhenFrame::StopFillWhenFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

StopFillWhenFrame::~StopFillWhenFrame()
{
}

void StopFillWhenFrame::render()
{
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("StpFillAt");

    navControls();
    oled->display();
}

void StopFillWhenFrame::button0()
{
    this->frameManager->setFrame(new StartFillWhenFrame(oled, frameManager));
}
void StopFillWhenFrame::button1()
{
    this->frameManager->setFrame(new WaterDepthFrame(oled, frameManager));
}
void StopFillWhenFrame::button2()
{
}
void StopFillWhenFrame::button3()
{
}