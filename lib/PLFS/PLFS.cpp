#include "PLFS.h"

PLFS::PLFS()
{
    struct pfs_pfs *pfs;
    struct lfs_config cfg;
    ffs_pico_createcfg(&cfg, ROOT_OFFSET, ROOT_SIZE);
    pfs = pfs_ffs_create(&cfg);
    int mountRes = pfs_mount(pfs, "/"); // check if mounts
    printf("Mount result: %u\n", mountRes);
}

PLFS::~PLFS()
{
}

bool PLFS::read(const char *fileName)
{
    FILE *rFile = fopen(fileName, "r");
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
        return true;
    }
    else
    {
        return false;
    }
}

bool PLFS::write(const char *fileName)
{
    FILE *wFile = fopen(fileName, "w"); // "w" erases file if it already exists
    if (wFile)
    {
        printf("wFile opened\n");
        char buffer[] = "Some text to write";
        fwrite(buffer, sizeof(char), sizeof(buffer), wFile);
        fclose(wFile);
        printf("wFile written to and closed\n");
        return true;
    }
    else
    {
        printf("F2 could not be opened for writing\n");
        return false;
    }
}