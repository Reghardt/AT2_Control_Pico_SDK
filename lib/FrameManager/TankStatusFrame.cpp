#include "TankStatusFrame.h"

TankStatusFrame::TankStatusFrame(SH1106 *oled, FrameManager *frameManager) : Frame::Frame(oled, frameManager)
{
}

TankStatusFrame::~TankStatusFrame()
{
}

void TankStatusFrame::render()
{

    if (editMode)
    {
        TankState::calculateLevel(50);

        oled->clearDisplay();
        const char heading[] = "State";

        oled->setTextColor(1);
        oled->setTextSize(2);
        oled->setCursor(0, 0);
        oled->print(heading);
        oled->write(' ');
        oled->print(std::to_string(TankState::getCurrentPercentage()).c_str());

        oled->write('%');
        oled->write('\n');
        oled->print(std::to_string(TankState::getCurrentLiters()).c_str());
        oled->print("L");
        oled->write('\n');
        oled->print(std::to_string(tempValue).c_str());

        editControls();
    }
    else
    {
        TankState::calculateLevel(50);

        oled->clearDisplay();
        const char heading[] = "State";

        oled->setTextColor(1);
        oled->setTextSize(2);
        oled->setCursor(0, 0);
        oled->print(heading);
        oled->write(' ');
        oled->print(std::to_string(TankState::getCurrentPercentage()).c_str());

        oled->write('%');
        oled->write('\n');
        oled->print(std::to_string(TankState::getCurrentLiters()).c_str());
        oled->print("L");
        oled->write('\n');
        oled->print(std::to_string(TankState::getMode()).c_str());

        navControls();
    }

    oled->display();
}

void TankStatusFrame::button0()
{
    if (editMode)
    {
        tempValue = (tempValue + 1) % 4;
        this->render();
    }
    else
    {
        this->frameManager->setFrame(new TankRadiusFrame(oled, frameManager));
    }
}
void TankStatusFrame::button1()
{
    if (editMode)
    {
        tempValue = (4 + (tempValue - 1) % 4) % 4;
        this->render();
    }
    else
    {
        this->frameManager->setFrame(new StartFillWhenFrame(oled, frameManager));
    }
}
void TankStatusFrame::button2()
{
    if (editMode)
    {
        TankState::setMode(tempValue);
        this->editMode = false;
        this->render();
    }
    else
    {
        tempValue = TankState::getMode();
        this->editMode = true;
        this->render();
    }
}
void TankStatusFrame::button3()
{
}