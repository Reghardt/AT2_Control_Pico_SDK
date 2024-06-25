#pragma once
#include "lfs.h"
#include <pfs.h>
#include <stdio.h>
#include "pico/stdlib.h"

#define ROOT_SIZE 0x20000    // flash LFS size, last 0.125mb of flash
#define ROOT_OFFSET 0x1E0000 // offset from start of flash

class PLFS
{
private:
    static bool mounted;
    static void mount();

public:
    static uint16_t read(const char *fileName, char *&buffer);
    static bool write(const char *fileName, const char *buffer, uint8_t length);
};
