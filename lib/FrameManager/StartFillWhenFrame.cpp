#include "StartFillWhenFrame.h"

StartFillWhenFrame::StartFillWhenFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

StartFillWhenFrame::~StartFillWhenFrame()
{
}

void StartFillWhenFrame::render()
{
    oled->clearDisplay();
    const char heading[] = "StrtFillAt";

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
        oled->print(std::to_string(TankCFG::getStartFillWhen()).c_str());
        oled->write('%');
        navControls();
        oled->display();
    }
}

void StartFillWhenFrame::button0()
{
    if (editMode)
    {
        tempValue += 5;
        render();
    }
    else
    {
        this->frameManager->setFrame(new TankStatusFrame(oled, frameManager));
    }
}
void StartFillWhenFrame::button1()
{
    if (editMode)
    {
        tempValue -= 5;
        render();
    }
    else
    {
        this->frameManager->setFrame(new StopFillWhenFrame(oled, frameManager));
    }
}
void StartFillWhenFrame::button2()
{
    if (editMode)
    {
        TankCFG::setStartFillWhen(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankCFG::getStartFillWhen();
        this->editMode = true;
        this->render();
    }
}
void StartFillWhenFrame::button3()
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