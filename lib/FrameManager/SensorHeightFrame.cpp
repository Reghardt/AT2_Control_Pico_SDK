#include "SensorHeightFrame.h"

SensorHeightFrame::SensorHeightFrame(SH1106 *oled, FrameManager *frameManager) : Frame(oled, frameManager)
{
}

SensorHeightFrame::~SensorHeightFrame()
{
}

void SensorHeightFrame::render()
{
    oled->drawCircle(40, 40, 8, 1);
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("Sen Height");

    navControls();

    oled->display();
}

void SensorHeightFrame::button0()
{
    this->frameManager->setFrame(new WaterDepthFrame(oled, frameManager));
}
void SensorHeightFrame::button1()
{
    this->frameManager->setFrame(new TankStatusFrame(oled, frameManager));
}
void SensorHeightFrame::button2()
{
}
void SensorHeightFrame::button3()
{
}