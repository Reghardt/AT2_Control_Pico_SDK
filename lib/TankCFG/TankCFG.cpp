#include "TankCFG.h"

json TankCFG::cfg;
const char *fileName = "TankCFG.json"; // string literals are automatically null terminated by the compiler

void TankCFG::setAndSaveProperty(const char *propertyName, uint16_t value)
{
    if (cfg.empty())
    {
        loadCFG();
    }

    cfg[propertyName] = value;

    std::string jDump = cfg.dump() + '\0';
    write(fileName, jDump.c_str(), jDump.length());
}

uint16_t TankCFG::getProperty(const char *propertyName)
{
    if (cfg.empty())
    {
        loadCFG();
    }
    auto propertyValue = cfg.template get<uint16_t>();
    return propertyValue;
}

void TankCFG::loadCFG()
{
    char *buffer = nullptr;
    if (read(fileName, buffer) > 0)
    {
        cfg = json::parse(buffer, nullptr, false);
        if (cfg.is_discarded())
        {
            printf("Could not parse json from file.\n");
            createDefaultCFG();
        }
        free(buffer);
    }
    else
    {
        createDefaultCFG();
    }
}

void TankCFG::createDefaultCFG()
{
    cfg["stopFillWhen"] = 80;
    cfg["startFillWhen"] = 20;
    cfg["sensorHeight"] = 20;
    cfg["waterDepth"] = 200;

    std::string cfgDump = cfg.dump() + '\0'; // dump json object to string, add null terminator
    write(fileName, cfgDump.c_str(), cfgDump.length());
}

void TankCFG::setStartFillWhen(uint8_t fillWhen)
{
    setAndSaveProperty("startFillWhen", fillWhen);
}
void TankCFG::setStopFillWhen(uint8_t stopFillWhen)
{
    setAndSaveProperty("stopFillWhen", stopFillWhen);
}
void TankCFG::setWaterDepth(uint16_t waterDepth)
{
    setAndSaveProperty("waterDepth", waterDepth);
}
void TankCFG::setSensorHeight(uint16_t sensorHeight)
{
    setAndSaveProperty("sensorHeight", sensorHeight);
}

uint16_t TankCFG::getStartFillWhen()
{
    return getProperty("startFillWhen");
}

uint16_t TankCFG::getStopFillWhen()
{
    return getProperty("stopFillWhen");
}

uint16_t TankCFG::getWaterDepth()
{
    return getProperty("waterDepth");
}

uint16_t TankCFG::getSensorHeight()
{
    return getProperty("sensorHeight");
}