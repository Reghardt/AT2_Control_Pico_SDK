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

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_SCK 18
#define PIN_MOSI 19

#define OLED_HEIGHT 64
#define OLED_WIDTH 128

#define OLED_I2C_ADDR _u(0x3C)

// 400 is usual, but often these can be overclocked to improve display response.
// Tested at 1000 on both 32 and 84 pixel height devices and it worked.
#define I2C_CLK 400
#define SDA_PIN 2
#define CLK_PIN 3

SH1106 oled = SH1106(i2c1, OLED_I2C_ADDR, OLED_WIDTH, OLED_HEIGHT);
LoRaClass loraClass = LoRaClass();

static char event_str[128];

static const char *gpio_irq_str[] = {
    "LEVEL_LOW",  // 0x1
    "LEVEL_HIGH", // 0x2
    "EDGE_FALL",  // 0x4
    "EDGE_RISE"   // 0x8
};

void gpio_callback(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    json j;
    j["pi"] = 3.141;

    printf(j.dump().c_str());

    struct pfs_pfs *pfs;
    struct lfs_config cfg;
    ffs_pico_createcfg(&cfg, ROOT_OFFSET, ROOT_SIZE);
    pfs = pfs_ffs_create(&cfg);
    int mountRes = pfs_mount(pfs, "/"); // check if mounts
    printf("Mount result: %u\n", mountRes);

    FILE *wFile = fopen("/test.txt", "w");
    if (wFile)
    {
        printf("wFile opened\n");
        char buffer[] = "Some text to write";
        fwrite(buffer, sizeof(char), sizeof(buffer), wFile);
        fclose(wFile);
        printf("wFile written to and closed\n");
    }
    else
    {
        printf("F2 could not be opened for writing\n");
    }

    FILE *rFile = fopen("/test.txt", "r");
    if (rFile)
    {
        printf("rFile opened\n");
        fseek(rFile, 0, SEEK_END);  // file stream pos to EOF
        long f1Size = ftell(rFile); // get file size
        printf("rFile size: %u\n", f1Size);
        rewind(rFile); // reset file stream pos to SOF

        char *buffer = (char *)malloc(sizeof(char) * f1Size);
        fread(buffer, 1, f1Size, rFile);
        printf(buffer);
        free(buffer);
        fclose(rFile);
    }

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    gpio_set_irq_callback(&gpio_callback);

    loraClass.begin(868E6);
    loraClass.setTxPower(13);
    loraClass.setSignalBandwidth(62.5E3);
    loraClass.setCodingRate4(5);
    loraClass.setSpreadingFactor(7);
    loraClass.setGain(6);
    loraClass.enableCrc();
    loraClass.enableInterruptOnReceive();
    loraClass.receive();

    // I2C is "open drain", pull ups to keep signal high when no data is being
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

    // oled.drawCircle(80, 30, 10, 1);
    // oled.setTextSize(2);
    // oled.setTextColor(1);
    // oled.write('T');
    // oled.write('a');
    // oled.write('n');
    // oled.write('k');
    // oled.write(' ');
    // oled.write('1');
    // oled.write('\n');
    // oled.write('8');
    // oled.write('0');
    // oled.write('%');
    // oled.setTextSize(1);
    // oled.setCursor(0, 57);
    // oled.write('0');
    // oled.setCursor(30, 57);
    // oled.write('1');
    // oled.setCursor(90, 57);
    // oled.write('2');
    // oled.setCursor(120, 57);
    // oled.write('3');

    oled.display();
    if (watchdog_caused_reboot())
    {
        printf("Rebooted by Watchdog!\n");
    }

    watchdog_enable(3000, true);
    watchdog_update();

    while (true)
    {
        // printf("Hello, world!\n");
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        // sleep_ms(500);
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        // sleep_ms(500);
        watchdog_update();
        frameManager.tick();
    }
}

void gpio_event_string(char *buf, uint32_t events)
{
    for (uint i = 0; i < 4; i++)
    {
        uint mask = (1 << i);
        if (events & mask)
        {
            // Copy this event string into the user string
            const char *event_str = gpio_irq_str[i];
            while (*event_str != '\0')
            {
                *buf++ = *event_str++;
            }
            events &= ~mask;

            // If more events add ", "
            if (events)
            {
                *buf++ = ',';
                *buf++ = ' ';
            }
        }
    }
    *buf++ = '\0';
}

void gpio_callback(uint gpio, uint32_t events)
{
    // Put the GPIO event(s) that just happened into event_str
    // so we can print it
    gpio_event_string(event_str, events);
    printf("GPIO %d %s\n", gpio, event_str);

    if (gpio == 10)
    {
        loraClass.handleDio0Rise();
    }
}
