// Loads and initializes game ROMs for emulation.

#include "rom.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct rom gb_rom;

unsigned char nintendo_logo[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
    0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
    0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
};

char *cartridge_types[] = {
    [0x00] = "ROM Only",
    [0x01] = "MBC1",
    [0x02] = "MBC1 + RAM",
    [0x03] = "MBC1 + RAM + Battery",
    [0x05] = "MBC2",
    [0x06] = "MBC2 + RAM + Battery",
    [0x08] = "ROM + RAM",
    [0x09] = "ROM + RAM + Battery",
    [0x0B] = "MMM01",
    [0x0C] = "MMM01 + RAM",
    [0x0D] = "MMM01 + RAM + Battery",
    [0x0F] = "MBC3 + Timer + Battery",
    [0x10] = "MBC3 + RAM + Timer + Battery",
    [0x11] = "MBC3",
    [0x12] = "MBC3 + RAM",
    [0x13] = "MBC3 + RAM + Battery",
    [0x19] = "MBC5",
    [0x1A] = "MBC5 + RAM",
    [0x1B] = "MBC5 + RAM + Battery",
    [0x1C] = "MBC5 + Rumble",
    [0x1D] = "MBC5 + RAM + Rumble",
    [0x1E] = "MBC5 + RAM + Battery + Rumble",
    [0x20] = "MBC6 + RAM + Battery",
    [0x22] = "MBC7 + RAM + Battery + Accelerometer",
    [0xFC] = "POCKET CAMERA",
    [0xFD] = "BANDAI TAMA5",
    [0xFE] = "HuC3",
    [0xFF] = "HuC1 + RAM + Battery",
};

char *rom_sizes[] = { [0x00] = "32KB",  [0x01] = "64KB",  [0x02] = "128KB",
                      [0x03] = "256KB", [0x04] = "512KB", [0x05] = "1MB",
                      [0x06] = "2MB",   [0x07] = "4MB",   [0x08] = "8MB" };

char *ram_sizes[] = { [0x00] = "None", [0x01] = "2KB",   [0x02] = "8KB",
                      [0x03] = "32KB", [0x04] = "128KB", [0x05] = "64KB" };

char *regions[] = { [0x00] = "Japan", [0x01] = "Non-Japan" };

int rom_init(unsigned char *rombytes)
{
    // 0x100-0x14F of the ROM is reserved for some special information

    // 0x100 – 0x103 – Start Vector
    // Game execution starts at 0x100

    // 0x104 – 0x133 – Nintendo Logo (48 bits)
    // Check if the cartridge is corrupted
    if (memcmp(&rombytes[0x104], nintendo_logo, sizeof(nintendo_logo)) != 0)
    {
        fprintf(stderr, "error: ROM corrupted\n");
        return EXIT_FAILURE;
    }

    // 0x134 – 0x143 – Game Title (16 bits)
    //     0x13F – 0x142 – Manufacturer Code (4 bits)
    //
    //     0x143 – GBC Flag (1 bit)
    //     Only used in CGB/AGB/AGS

    memcpy(gb_rom.game_title, &rombytes[0x134], 16);
    gb_rom.game_title[15] = '\0';

    // 0x144 – 0x145 – New Licensee Code (2 bits)
    //     Only used in games released after the SGB

    // 0x146 – SGB Flag (1 bit)
    // 0x03: SGB functions; others: no SGB functions

    // 0x147 – Cartridge Type (1 bit)
    // Specifies the MBC, and aditional hardware
    gb_rom.cartridge_type = rombytes[0x147];

    // 0x148 – ROM Size (1 bit)
    // Specifies the ROM size
    gb_rom.rom_size = rombytes[0x148];

    // 0x149 – RAM Size (1 bit)
    // Specifies the RAM size
    gb_rom.ram_size = rombytes[0x148];

    // 0x14A – Destination Code (1 bit)
    // 0x00: game from Japan; others: game from Non-Japan
    gb_rom.region = rombytes[0x14A];

    // 0x14B – Old Licensee Code (1 bit)
    // Specifies the company or publisher of the game
    // 0x33: New Licensee Code at 0x144-0x145 is used instead

    // 0x14C – ROM Version (1 bit)
    // Specifies the ROM version
    gb_rom.version = rombytes[0x14C];

    // 0x14D – Header Checksum (1 bit)
    // Contains a checksum of the cartridge header bytes 0x13-0x14C
    for (int i = 0x0134; i <= 0x014C; i++)
        gb_rom.checksum = gb_rom.checksum - rombytes[i] - 1;

    // 0x14E – 0x14F – Global Checksum (2 bits)
    // 16 bit checksum (upper byte in 0x14E) of the whole ROM
    // Not verified in the Game Boy

    // Print all informations about the ROM
    printf("ROM Informations\n================\n");
    printf("ROM Title: %s\n", gb_rom.game_title);
    printf("Cartridge Type: %s (0x%02X)\n",
           cartridge_types[gb_rom.cartridge_type], gb_rom.cartridge_type);
    printf("ROM Size: %s (0x%02X)\n", rom_sizes[gb_rom.rom_size],
           gb_rom.rom_size);
    printf("RAM Size: %s (0x%02X)\n", ram_sizes[gb_rom.ram_size],
           gb_rom.ram_size);
    printf("Region: %s (0x%02X)\n", regions[gb_rom.region], gb_rom.region);
    printf("Version: 0x%02X\n", gb_rom.version);
    if (rombytes[0x14D] == gb_rom.checksum)
        printf("Checksum: OK (0x%02X)\n", gb_rom.checksum);
    else
    {
        printf("Checksum: FAIL (0x%02X)\n================\n", gb_rom.checksum);
        return EXIT_FAILURE;
    }
    printf("================\n");

    return EXIT_SUCCESS;
}

int rom_load(const char *filename)
{
    struct stat st;

    // Open the ROM file in read-only mode
    int fd = open(filename, O_RDONLY);
    if (fd == -1 || fstat(fd, &st) == -1)
    {
        fprintf(stderr, "error: failed to open file '%s'\n", filename);
        if (fd != -1)
            close(fd);
        return EXIT_FAILURE;
    }

    // Allocate memory for the ROM
    gb_rom.rom_data = malloc(st.st_size);
    if (!gb_rom.rom_data)
    {
        fprintf(stderr, "error: failed to allocate memory for ROM\n");
        close(fd);
        return EXIT_FAILURE;
    }

    // Read the ROM data
    ssize_t bytes_read = read(fd, gb_rom.rom_data, st.st_size);
    if (bytes_read != st.st_size)
    {
        fprintf(stderr, "error: failed to read ROM data completely\n");
        free(gb_rom.rom_data);
        close(fd);
        return EXIT_FAILURE;
    }

    // Initialize ROM structure
    int result = rom_init(gb_rom.rom_data);

    close(fd);
    return result;
}

unsigned char *rom_getdata(void)
{
    return gb_rom.rom_data;
}

void free_rom(void)
{
    free(gb_rom.rom_data);
}
