#ifndef ROM_H
#define ROM_H

#include <stdio.h>

struct rom
{
    char game_title[16];
    unsigned int cartridge_type;
    unsigned int rom_size;
    unsigned int ram_size;
    unsigned int region;
    unsigned int version;
    unsigned char checksum;
    unsigned char *rom_data;
};

int rom_init(unsigned char *rombytes);
int rom_load(const char *filename);

unsigned char *rom_getdata(void);
void free_rom(void);

#endif /* !ROM_H */
