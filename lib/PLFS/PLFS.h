#pragma once
#include "lfs.h"
#include <pfs.h>

#define ROOT_SIZE 0x20000    // flash LFS size, last 0.125mb of flash
#define ROOT_OFFSET 0x1E0000 // offset from start of flash

class PLFS
{
private:
public:
    PLFS();
    ~PLFS();

    bool read(const char *fileName);
    bool write(const char *fileName);
};
