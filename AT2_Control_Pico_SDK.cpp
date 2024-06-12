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

// flash filesystem size
#define ROOT_SIZE 0x100000
#define ROOT_OFFSET 0x100000

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

int main()
{
    stdio_init_all();

    struct pfs_pfs *pfs;
    struct lfs_config cfg;
    ffs_pico_createcfg(&cfg, ROOT_OFFSET, ROOT_SIZE);
    pfs = pfs_ffs_create(&cfg);
    pfs_mount(pfs, "/"); // check if mounts

    FILE *f2 = fopen("/test.txt", "w");
    if (f2)
    {
        printf("F2 opened\n");
        char buffer[] = "Control Test 2";
        fwrite(buffer, sizeof(char), sizeof(buffer), f2);
        fclose(f2);
        printf("F2 written to and closed\n");
    }
    else
    {
        printf("F2 could not be opened\n");
    }

    FILE *f1 = fopen("/test.txt", "r");
    if (f1)
    {
        printf("F1 opened\n");
        fseek(f1, 0, SEEK_END);
        auto f1Size = ftell(f1);
        printf("f1size: %u\n", f1Size);
        rewind(f1);

        char *buffer = (char *)malloc(sizeof(char) * f1Size);
        fread(buffer, 1, f1Size, f1);
        printf(buffer);
        free(buffer);
        fclose(f1);
    }

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // SPI initialisation at 1MHz.
    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_dir(PIN_CS, GPIO_OUT); // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_put(PIN_CS, 1);
    bi_decl(bi_2pins_with_func(SDA_PIN, CLK_PIN, GPIO_FUNC_I2C)); // useful information for picotool
    bi_decl(bi_program_description("OLED driver I2C example for the Raspberry Pi Pico"));

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
