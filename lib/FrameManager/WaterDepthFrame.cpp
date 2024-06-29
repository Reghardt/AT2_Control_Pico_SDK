#include "WaterDepthFrame.h"

WaterDepthFrame::WaterDepthFrame(SH1106 *oled, FrameManager *frameManager) : Frame(oled, frameManager)
{
    sensorHeightValue = TankCFG::getSensorHeight();
}

WaterDepthFrame::~WaterDepthFrame()
{
}

void WaterDepthFrame::render()
{
    oled->clearDisplay();
    const char heading[] = "WaterDepth";

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
        oled->print(std::to_string(TankCFG::getWaterDepth()).c_str());
        oled->print("cm");
        navControls();
        oled->display();
    }
}

void WaterDepthFrame::button0()
{
    if (editMode)
    {
        if (tempValue + step + sensorHeightValue <= 450)
        {
            tempValue += step;
        }
        render();
    }
    else
    {
        this->frameManager->setFrame(new StopFillWhenFrame(oled, frameManager));
    }
}
void WaterDepthFrame::button1()
{
    if (editMode)
    {
        if ((tempValue - step) <= 30)
        {
            tempValue = 30;
        }
        else
        {
            tempValue -= 5;
        }
        render();
    }
    else
    {
        this->frameManager->setFrame(new SensorHeightFrame(oled, frameManager));
    }
}
void WaterDepthFrame::button2()
{
    if (editMode)
    {
        TankCFG::setWaterDepth(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankCFG::getWaterDepth();
        this->editMode = true;
        this->render();
    }
}
void WaterDepthFrame::button3()
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