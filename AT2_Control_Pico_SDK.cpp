#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/watchdog.h"
#include "pico/cyw43_arch.h"
#include "SH1106.h"
#include "Frame.h"
#include "Tank.h"
#include "lfs.h"
#include <pfs.h>
#include "FrameManager.h"
#include <nlohmann/json.hpp>
#include "LoRa.h"
#include "hardware/gpio.h"

using json = nlohmann::json;

// flash filesystem size
#define ROOT_SIZE 0x20000    // flash LFS size, 0.125mb
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
LoRa loraClass = LoRa(spi1, LORA_CS_PIN, LORA_RST_PIN, LORA_DIO0_PIN);

void gpio_irq_callback(uint gpio, uint32_t events)
{
    printf("IRQ: GPIO %d\n", gpio);
    if (gpio == LORA_DIO0_PIN)
    {
        loraClass.handleDio0Rise();
    }
}

void loraOnReceive(int packetSize)
{
    for (int i = 0; i < packetSize; i++)
    {
        printf("Read: %c\n", loraClass.read());
    }
    int rssi = loraClass.packetRssi();
    int snr = loraClass.packetSnr();
}

int main()
{
    stdio_init_all();

    json j;
    j["pi"] = 3.141;

    printf(j.dump().c_str());

    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    loraClass.begin(868E6);
    loraClass.setTxPower(13);
    loraClass.setSignalBandwidth(62.5E3);
    loraClass.setCodingRate4(5);
    loraClass.setSpreadingFactor(7);
    loraClass.setGain(6);
    loraClass.enableCrc();
    loraClass.onReceive(&loraOnReceive);
    loraClass.receive();

    gpio_set_irq_callback(&gpio_irq_callback);

    i2c_init(i2c1, I2C_CLK * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(CLK_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(CLK_PIN);

    oled.begin();
    oled.display();

    FrameManager frameManager = FrameManager(&oled);
    frameManager.setFrame(new Tank(&oled, &frameManager));
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
