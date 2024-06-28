#pragma once

#include "PLFS.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TankCFG : public PLFS
{
private:
    static json cfg;
    static const char *fileName;

    static void setAndSaveProperty(const char *propertyName, uint16_t value);
    static uint16_t getProperty(const char *propertyName);

    static void loadCFG();

    static void createDefaultCFG();

public:
    static void setStartFillWhen(uint16_t fillWhen);
    static void setStopFillWhen(uint16_t stopFillWhen);
    static void setWaterDepth(uint16_t waterDepth);
    static void setSensorHeight(uint16_t sensorHeight);

    static uint16_t getStartFillWhen();
    static uint16_t getStopFillWhen();

    static uint16_t getWaterDepth();
    static uint16_t getSensorHeight();
};
