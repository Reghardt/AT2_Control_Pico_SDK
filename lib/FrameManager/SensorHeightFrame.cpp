#include "SensorHeightFrame.h"

SensorHeightFrame::SensorHeightFrame(SH1106 *oled, FrameManager *frameManager) : Frame(oled, frameManager)
{
    waterDepthValue = TankCFG::getWaterDepth();
}

SensorHeightFrame::~SensorHeightFrame()
{
}

void SensorHeightFrame::render()
{
    oled->clearDisplay();
    const char heading[] = "Sen Height";

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
        oled->print(std::to_string(TankCFG::getSensorHeight()).c_str());
        oled->print("cm");
        navControls();
        oled->display();
    }
}

void SensorHeightFrame::button0()
{
    if (editMode)
    {
        if (tempValue + step + waterDepthValue <= 450)
        {
            tempValue += step;
        }
        render();
    }
    else
    {
        this->frameManager->setFrame(new WaterDepthFrame(oled, frameManager));
    }
}
void SensorHeightFrame::button1()
{
    if (editMode)
    {
        if ((tempValue - step) <= 20)
        {
            tempValue = 20;
        }
        else
        {
            tempValue -= step;
        }
        render();
    }
    else
    {
        this->frameManager->setFrame(new TankRadiusFrame(oled, frameManager));
    }
}
void SensorHeightFrame::button2()
{
    if (editMode)
    {
        TankCFG::setSensorHeight(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankCFG::getSensorHeight();
        this->editMode = true;
        this->render();
    }
}
void SensorHeightFrame::button3()
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