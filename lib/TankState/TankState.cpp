#include "TankState.h"

bool TankState::awaitingFirstReading = true;
uint16_t TankState::currentPercentage = 0;
uint16_t TankState::currentLiters = 0;
uint8_t TankState::mode = 0;
bool TankState::pumpState = false;
uint16_t TankState::lastDepthMeasurement = 0;

TankState::TankState(/* args */)
{
}

TankState::~TankState()
{
}

uint16_t TankState::getCurrentPercentage()
{
    return currentPercentage;
}

uint16_t TankState::getCurrentLiters()
{
    return currentLiters;
}

void TankState::calculateLevel(uint16_t reading)
{
    uint16_t depthMeasurement = TankCFG::getWaterDepth() - (reading - TankCFG::getSensorHeight());
    uint16_t adjustedDepthMeasurement;
    if (lastDepthMeasurement == 0)
    {
        adjustedDepthMeasurement = depthMeasurement;
    }
    else if (lastDepthMeasurement != depthMeasurement)
    {
        if (depthMeasurement > lastDepthMeasurement)
        {
            adjustedDepthMeasurement = lastDepthMeasurement + 1;
        }
        else
        {
            adjustedDepthMeasurement = lastDepthMeasurement - 1;
        }
    }

    float prePercentage = ((float)adjustedDepthMeasurement / (float)TankCFG::getWaterDepth());
    currentPercentage = prePercentage * 100;

    printf("Pre percentage %f\n", prePercentage);
    float tankArea = M_PI * pow(TankCFG::getTankRadius(), 2);
    printf("Tank area: %f\n", tankArea);

    float liters = (float)(TankCFG::getWaterDepth()) * prePercentage * tankArea / 1000.0;
    printf("liters: %f\n", liters);
    currentLiters = (uint16_t)(liters);
}

uint8_t TankState::getMode()
{
    return mode;
}

void TankState::setMode(uint8_t newMode)
{
    mode = newMode;
}

void TankState::setPumpState(bool newPumpState)
{
    pumpState = newPumpState;
    gpio_put(20, newPumpState);
}

bool TankState::getPumpState()
{
    return pumpState;
}
