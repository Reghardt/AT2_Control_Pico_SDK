#include "TankRadiusFrame.h"

TankRadiusFrame::TankRadiusFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

TankRadiusFrame::~TankRadiusFrame()
{
}

void TankRadiusFrame::render()
{
    oled->clearDisplay();
    const char heading[] = "Radius";

    if (editMode)
    {
        oled->setTextColor(1);
        oled->setTextSize(2);
        oled->setCursor(0, 0);
        oled->print(heading);
        oled->write('\n');
        oled->print(std::to_string(tempValue).c_str());
        oled->print("cm");
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
        oled->print(std::to_string(TankCFG::getTankRadius()).c_str());
        oled->print("cm");
        navControls();
        oled->display();
    }
}

void TankRadiusFrame::button0()
{
    if (editMode)
    {
        tempValue += step;
        render();
    }
    else
    {
        this->frameManager->setFrame(new SensorHeightFrame(oled, frameManager));
    }
}
void TankRadiusFrame::button1()
{
    if (editMode)
    {
        if ((tempValue - step) >= step)
        {
            tempValue -= step;
        }
        render();
    }
    else
    {
        this->frameManager->setFrame(new TankStatusFrame(oled, frameManager));
    }
}
void TankRadiusFrame::button2()
{
    if (editMode)
    {
        TankCFG::setTankRadius(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankCFG::getTankRadius();
        this->editMode = true;
        this->render();
    }
}
void TankRadiusFrame::button3()
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