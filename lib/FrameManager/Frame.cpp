#include "Frame.h"

Frame::Frame(SH1106 *oled, FrameManager *frameManager) : oled(oled), frameManager(frameManager)
{
}

Frame::~Frame()
{
}