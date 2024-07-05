#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "TankCFG.h"

class TankState
{
private:
    static bool awaitingFirstReading;
    static uint16_t currentPercentage;
    static uint16_t currentLiters;

    /**
     * 0 = off
     * 1 = auto
     * 2 = fill & auto
     * 3 = fill & off
     *
     */
    static uint8_t mode;
    static bool pumpState;

public:
    TankState();
    ~TankState();

    static uint16_t getCurrentPercentage();
    static uint16_t getCurrentLiters();

    static void calculateLevel(uint16_t reading);

    static uint8_t getMode();

    static void setMode(uint8_t newMode);

    static void setPumpState(bool newPumpState);

    static bool getPumpState();
};