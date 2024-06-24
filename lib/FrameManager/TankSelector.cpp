#include "TankSelector.h"

TankSelector::TankSelector(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

TankSelector::~TankSelector()
{
}

void TankSelector::render()
{
    oled->setTextColor(1);
    oled->setTextSize(2);
    oled->setCursor(0, 0);
    oled->print("Select T");
    oled->display();

    oled->setTextSize(1);
    oled->setCursor(0, 58);
    oled->write('^');
}

void TankSelector::button0()
{
}
void TankSelector::button1()
{
}
void TankSelector::button2()
{
}
void TankSelector::button3()
{
}
