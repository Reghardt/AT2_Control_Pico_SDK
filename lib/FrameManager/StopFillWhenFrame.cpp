#include "StopFillWhenFrame.h"

StopFillWhenFrame::StopFillWhenFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

StopFillWhenFrame::~StopFillWhenFrame()
{
}

void StopFillWhenFrame::render()
{
    oled->clearDisplay();
    const char heading[] = "EndFillAt";

    if (editMode)
    {
        oled->setTextColor(1);
        oled->setTextSize(2);
        oled->setCursor(0, 0);
        oled->print(heading);
        oled->write('\n');
        oled->print(std::to_string(tempValue).c_str());
        oled->write('%');
        oled->write('\n');
        oled->setTextSize(1);
        oled->print("(edit mode)");
        editControls();
        oled->display();
    }
    else
    {
        oled->setTextColor(1);
        oled->setTextSize(2);
        oled->setCursor(0, 0);
        oled->print(heading);
        oled->write('\n');
        oled->print(std::to_string(TankCFG::getStopFillWhen()).c_str());
        oled->write('%');
        navControls();
        oled->display();
    }
}

void StopFillWhenFrame::button0()
{
    if (editMode)
    {
        tempValue += 5;
        render();
    }
    else
    {
        this->frameManager->setFrame(new StartFillWhenFrame(oled, frameManager));
    }
}

void StopFillWhenFrame::button1()
{
    if (editMode)
    {
        tempValue -= 5;
        render();
    }
    else
    {
        this->frameManager->setFrame(new WaterDepthFrame(oled, frameManager));
    }
}

void StopFillWhenFrame::button2()
{
    if (editMode)
    {
        TankCFG::setStopFillWhen(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankCFG::getStopFillWhen();
        this->editMode = true;
        this->render();
    }
}

void StopFillWhenFrame::button3()
{
    if (editMode)
    {
        this->editMode = false;
        this->render();
    }
    else
    {
    }
}