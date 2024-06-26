#include "WaterDepthFrame.h"

WaterDepthFrame::WaterDepthFrame(SH1106 *oled, FrameManager *frameManager) : Frame(oled, frameManager)
{
}

WaterDepthFrame::~WaterDepthFrame()
{
}

void WaterDepthFrame::render()
{
    oled->drawCircle(40, 40, 8, 1);
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("WaterDepth");

    navControls();
    oled->display();
}

void WaterDepthFrame::button0()
{
    this->frameManager->setFrame(new StopFillWhenFrame(oled, frameManager));
}
void WaterDepthFrame::button1()
{
    this->frameManager->setFrame(new SensorHeightFrame(oled, frameManager));
}
void WaterDepthFrame::button2()
{
}
void WaterDepthFrame::button3()
{
}