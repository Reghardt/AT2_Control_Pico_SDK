#include "Tank.h"

Tank::Tank(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

Tank::~Tank()
{
}

void Tank::render()
{
    oled->drawCircle(40, 40, 8, 1);
    oled->display();
}

void Tank::button0()
{
    printf("Tank b0\n");
    this->frameManager->setFrame(new FillWhen(oled, frameManager));
}
void Tank::button1()
{
}
void Tank::button2()
{
}
void Tank::button3()
{
}