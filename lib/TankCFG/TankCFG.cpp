#include "TankCFG.h"

json TankCFG::cfg;
const char *TankCFG::fileName = "TankCFG.json"; // string literals are automatically null terminated by the compiler

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

uint16_t TankCFG::getProperty(const char *propertyName, uint16_t defaultValue)
{

    loadCFG();

    // check if the property exists, if it does not, create it on the object
    if (cfg.contains(propertyName) == false)
    {
        cfg[propertyName] = defaultValue;
    }

    auto propertyValue = cfg[propertyName].template get<uint16_t>();
    // cfg.at(propertyName)

    return propertyValue;
}

void TankCFG::loadCFG()
{
    if (cfg.empty()) // empty ie, size of 0 bytes. {} is not empty
    {
        char *buffer = nullptr;
        if (read(fileName, buffer) > 0)
        {
            cfg = json::parse(buffer, nullptr, false);
            if (cfg.is_discarded())
            {
                printf("Could not parse json from file.\n");
                createEmptyCFG();
            }
            free(buffer);
        }
        else
        {
            createEmptyCFG();
        }
    }
}

void TankCFG::createEmptyCFG()
{
    // cfg["stopFillWhen"] = 80;
    // cfg["startFillWhen"] = 20;
    // cfg["sensorHeight"] = 20;
    // cfg["waterDepth"] = 200;

    // std::string cfgDump = cfg.dump() + '\0'; // dump json object to string, add null terminator
    std::string emptyCfg = "{}\0";
    write(fileName, emptyCfg.c_str(), emptyCfg.length());
}

void TankCFG::setStartFillWhen(uint16_t fillWhen)
{
    setAndSaveProperty("startFillWhen", fillWhen);
}
void TankCFG::setStopFillWhen(uint16_t stopFillWhen)
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

void TankCFG::setTankRadius(uint16_t tankRadius)
{
    setAndSaveProperty("tankRadius", tankRadius);
}

uint16_t TankCFG::getStartFillWhen()
{
    return getProperty("startFillWhen", 50);
}

uint16_t TankCFG::getStopFillWhen()
{
    return getProperty("stopFillWhen", 80);
}

uint16_t TankCFG::getWaterDepth()
{
    return getProperty("waterDepth", 300);
}

uint16_t TankCFG::getSensorHeight()
{
    return getProperty("sensorHeight", 50);
}

uint16_t TankCFG::getTankRadius()
{
    return getProperty("tankRadius", 50);
}