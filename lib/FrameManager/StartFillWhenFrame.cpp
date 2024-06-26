#include "StartFillWhenFrame.h"

StartFillWhenFrame::StartFillWhenFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

StartFillWhenFrame::~StartFillWhenFrame()
{
}

void StartFillWhenFrame::render()
{
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("Fill When");

    navControls();
    oled->display();
}

void StartFillWhenFrame::button0()
{
    this->frameManager->setFrame(new TankStatusFrame(oled, frameManager));
}
void StartFillWhenFrame::button1()
{
    this->frameManager->setFrame(new StopFillWhenFrame(oled, frameManager));
}
void StartFillWhenFrame::button2()
{
}
void StartFillWhenFrame::button3()
{
}