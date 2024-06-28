#include "TankStatusFrame.h"

TankStatusFrame::TankStatusFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

TankStatusFrame::~TankStatusFrame()
{
}

void TankStatusFrame::render()
{
    oled->clearDisplay();
    oled->drawCircle(40, 40, 8, 1);
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("Status");

    navControls();
    oled->display();
}

void TankStatusFrame::button0()
{
    this->frameManager->setFrame(new SensorHeightFrame(oled, frameManager));
}
void TankStatusFrame::button1()
{
    this->frameManager->setFrame(new StartFillWhenFrame(oled, frameManager));
}
void TankStatusFrame::button2()
{
}
void TankStatusFrame::button3()
{
}