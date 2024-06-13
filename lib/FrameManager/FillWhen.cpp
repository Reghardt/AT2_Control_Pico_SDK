
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
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->write('P');
    oled->write('a');
    oled->write('g');
    oled->write('e');
    oled->write(' ');
    oled->write('2');
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