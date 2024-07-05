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
        // TankState::calculateLevel(50);

        oled->clearDisplay();
        const char heading[] = "Level";

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
        // oled->print(std::to_string(tempValue).c_str());
        if (tempValue == 0)
        {
            oled->print("Off");
        }
        else if (tempValue == 1)
        {
            oled->print("Auto");
        }
        else if (tempValue == 2)
        {
            oled->print("Fill&Auto");
        }
        else
        {
            oled->print("Fill&Off");
        }

        editControls();
    }
    else
    {
        // TankState::calculateLevel(50);

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
        // oled->print(std::to_string(TankState::getMode()).c_str());

        uint8_t md = TankState::getMode();
        if (md == 0)
        {
            oled->print("Off");
        }
        else if (md == 1)
        {
            oled->print("Auto");
        }
        else if (md == 2)
        {
            oled->print("Fill&Auto");
        }
        else
        {
            oled->print("Fill&Off");
        }

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
        if (tempValue == 0) // off
        {
            TankState::setPumpState(false);
        }
        else if (tempValue == 1) // auto
        {
            if (TankState::getCurrentPercentage() <= TankCFG::getStartFillWhen())
            {
                TankState::setPumpState(true);
            }
        }
        else if (tempValue == 2) // Fill & Auto
        {
            if (TankState::getCurrentPercentage() < TankCFG::getStopFillWhen()) // if FILL & AUTO and WL under stop fill when
            {
                TankState::setPumpState(true); // fill
            }
            else // tank already over or at max level so set as AUTO and turn off pump
            {
                TankState::setPumpState(false);
                TankState::setMode(1); // set AUTO
            }
        }
        else // Fill & Off
        {

            if (TankState::getCurrentPercentage() < TankCFG::getStopFillWhen())
            {
                TankState::setPumpState(true);
            }
            else // tank already over max level so set as off and turn pump off
            {
                TankState::setPumpState(false);
                TankState::setMode(0); // Set OFF
            }
        }

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

// void TankStatusFrame::update()
// {
//     this->render();
// }