
#include "FillWhen.h"

FillWhen::FillWhen(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

FillWhen::~FillWhen()
{
}

void FillWhen::render()
{
    oled->drawCircle(40, 40, 10, 1);
    oled->display();
}

void FillWhen::button0()
{
    this->frameManager->setFrame(new Tank(oled, frameManager));
}
void FillWhen::button1()
{
}
void FillWhen::button2()
{
}
void FillWhen::button3()
{
}