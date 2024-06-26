#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/watchdog.h"
#include "pico/cyw43_arch.h"
#include "SH1106.h"
#include "Frame.h"
#include "TankStatusFrame.h"
// #include "lfs.h"
// #include <pfs.h>
#include "FrameManager.h"
#include <nlohmann/json.hpp>
#include "LoRa.h"
#include "hardware/gpio.h"
#include "TankSelector.h"
#include "TankCFG.h"

using json = nlohmann::json;

// flash filesystem size
#define ROOT_SIZE 0x20000    // flash LFS size, last 0.125mb of flash
#define ROOT_OFFSET 0x1E0000 // offset from start of flash

#define OLED_HEIGHT 64
#define OLED_WIDTH 128

#define OLED_I2C_ADDR _u(0x3C)

#define I2C_CLK 400
#define SDA_PIN 2
#define CLK_PIN 3

#define LORA_CS_PIN 13
#define LORA_RST_PIN 11
#define LORA_DIO0_PIN 10

SH1106 oled = SH1106(i2c1, OLED_I2C_ADDR, OLED_WIDTH, OLED_HEIGHT);
LoRa loRa = LoRa(spi1, LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);
// TankCFG tankCFG = TankCFG();

void gpio_irq_callback(uint gpio, uint32_t events)
{
    printf("IRQ: GPIO %d\n", gpio);
    if (gpio == LORA_DIO0_PIN)
    {
        loRa.handleDio0Rise();
    }
}

void loraOnReceive(int packetSize)
{
    std::vector<std::uint8_t> v_msgpack;
    for (int i = 0; i < packetSize; i++)
    {
        v_msgpack.push_back(loRa.read());
    }
    json j_from_msgpack = json::from_msgpack(v_msgpack, true, false);

    if (j_from_msgpack.is_discarded())
    {
        printf("Discarded\n");
        return;
    }
    else
    {
        printf("\nAccepted\n");
        printf("%s\n", j_from_msgpack.dump().c_str());
        printf("RSSI: %d\n", loRa.packetRssi());
        printf("SNR : %d\n", loRa.packetSnr());
    }
}

int main()
{
    stdio_init_all();
    // tankCFG.begin();

    printf("Start fill when: %u\n", TankCFG::getStartFillWhen());
    printf("Stop fill when: %u\n", TankCFG::getStopFillWhen());

    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    loRa.begin(868E6);
    loRa.setTxPower(13);
    loRa.setSignalBandwidth(62.5E3);
    loRa.setCodingRate4(5);
    loRa.setSpreadingFactor(7);
    loRa.setGain(6);
    loRa.enableCrc();
    loRa.onReceive(&loraOnReceive);
    loRa.receive();

    gpio_set_irq_callback(&gpio_irq_callback);

    i2c_init(i2c1, I2C_CLK * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(CLK_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(CLK_PIN);

    oled.begin();
    oled.display();

    FrameManager frameManager = FrameManager(&oled);
    frameManager.setFrame(new TankStatusFrame(&oled, &frameManager));
    frameManager.begin();

    oled.display();
    if (watchdog_caused_reboot())
    {
        printf("Rebooted by Watchdog!\n");
    }

    watchdog_enable(3000, true);
    watchdog_update();

    while (true)
    {
        watchdog_update();
        frameManager.tick();
    }
}
