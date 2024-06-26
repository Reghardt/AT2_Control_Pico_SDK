#include "Frame.h"

Frame::Frame(SH1106 *oled, FrameManager *frameManager) : oled(oled), frameManager(frameManager)
{
}

Frame::~Frame()
{
}

void Frame::navControls()
{
    oled->setTextColor(1);
    oled->setTextSize(1);
    oled->setCursor(0, 57);
    oled->write(0x18);
    oled->setCursor(30, 57);
    oled->write(0x19);
    oled->setCursor(70, 57);
    oled->print("Sel");
}