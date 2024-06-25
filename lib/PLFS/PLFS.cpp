#include "PLFS.h"

bool PLFS::mounted = false;

void PLFS::mount()
{
    struct pfs_pfs *pfs;
    struct lfs_config cfg;
    ffs_pico_createcfg(&cfg, ROOT_OFFSET, ROOT_SIZE);
    pfs = pfs_ffs_create(&cfg);
    int pfs_mount_result = pfs_mount(pfs, "/");
    if (pfs_mount_result != 0) // zero on success
    {
        while (true)
        {
            printf("ERROR: File system could not be mounted: %i\n", pfs_mount_result);
            sleep_ms(1000);
        }
    }
    else
    {
        printf("File system mounted\n");
        mounted = true;
    }
}

/**
 * Reads specified file's content into buffer. Returns bytes read.
 */
uint16_t PLFS::read(const char *fileName, char *&buffer)
{
    // mount if not mounted
    if (mounted == false)
    {
        mount();
    }

    // try to open the file for reading
    FILE *rFile = fopen(fileName, "r");

    if (rFile)
    {
        printf("rFile opened\n");
        fseek(rFile, 0, SEEK_END);    // file stream pos to EOF
        long fileSize = ftell(rFile); // get file size
        printf("rFile size: %u\n", fileSize);
        rewind(rFile); // reset file stream pos to SOF

        if (fileSize < 1)
        {
            return 0;
        }

        buffer = (char *)malloc(sizeof(char) * fileSize);
        fread(buffer, 1, fileSize, rFile);
        fclose(rFile);
        return fileSize;
    }
    else
    {
        return 0;
    }
}

bool PLFS::write(const char *fileName, const char *buffer, uint8_t length)
{
    if (mounted == false)
    {
        mount();
    }

    FILE *wFile = fopen(fileName, "w"); // "w" erases file if it already exists
    if (wFile)
    {
        printf("wFile opened\n");
        fwrite(buffer, sizeof(char), length, wFile);
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