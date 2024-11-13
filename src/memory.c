// Manages Game Boy memory, including RAM and memory mappings.

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rom.h"

struct memory *gb_memory;

int memory_init(void)
{
    // Retrieve ROM data
    unsigned char *rom_data = rom_getdata();

    // Allocate memory for the main memory structure
    gb_memory = malloc(sizeof(struct memory));
    if (!gb_memory)
    {
        fprintf(stderr, "error: failed to allocate memory\n");
        return EXIT_FAILURE;
    }

    gb_memory->rom0 = malloc(0x4000); // Fixed ROM bank (16KB)
    gb_memory->romx = malloc(0x4000); // Switchable ROM bank (16KB)
    if (!gb_memory->rom0 || !gb_memory->romx)
    {
        fprintf(stderr, "error: failed to allocate ROM memory\n");
        return EXIT_FAILURE;
    }

    // Copy the ROM data into the ROM banks
    memcpy(gb_memory->rom0, rom_data, 0x4000);
    memcpy(gb_memory->romx, rom_data + 0x4000, 0x4000);

    gb_memory->vram = calloc(1, 0x2000); //  Video RAM (8KB)
    gb_memory->sram = calloc(1, 0x2000); //  External (cartridge) RAM (8KB)
    gb_memory->wram0 = calloc(1, 0x1000); // Work RAM bank 0 (4KB)
    gb_memory->wramx = calloc(1, 0x1000); // Switchable Work RAM bank (4KB)
    gb_memory->oam = calloc(1, 0xA0); //     Sprite Attribute Table (160 bytes)
    gb_memory->io_regs = calloc(1, 0x80); // I/O registers (128 bytes)
    gb_memory->hram = calloc(1, 0x7F); //    High RAM (127 bytes)
    gb_memory->ie_reg = malloc(1); //        Interrupt Enable register

    return EXIT_SUCCESS;
}

unsigned char memory_read(struct memory *gb_memory, size_t address)
{
    if (address < 0x4000)
        return gb_memory->rom0[address];
    else if (address >= 0x4000 && address < 0x8000)
        return gb_memory->romx[address - 0x4000];
    else if (address >= 0x8000 && address < 0xA000)
        return gb_memory->vram[address - 0x8000];
    else if (address >= 0xA000 && address < 0xC000)
        return gb_memory->sram[address - 0xA000];
    else if (address >= 0xC000 && address < 0xD000)
        return gb_memory->wram0[address - 0xC000];
    else if (address >= 0xD000 && address < 0xE000)
        return gb_memory->wramx[address - 0xD000];
    else if (address >= 0xFE00 && address < 0xFEA0)
        return gb_memory->oam[address - 0xFE00];
    else if (address >= 0xFF00 && address < 0xFF80)
        return gb_memory->io_regs[address - 0xFF00];
    else if (address >= 0xFF80 && address < 0xFFFF)
        return gb_memory->hram[address - 0xFF80];
    else if (address == 0xFFFF)
        return *gb_memory->ie_reg;

    return 0xFF;
}

void memory_write(struct memory *gb_memory, size_t address, size_t value)
{
    if (address >= 0x8000 && address < 0xA000)
        gb_memory->vram[address - 0x8000] = value;
    else if (address >= 0xA000 && address < 0xC000)
        gb_memory->sram[address - 0xA000] = value;
    else if (address >= 0xC000 && address < 0xD000)
        gb_memory->wram0[address - 0xC000] = value;
    else if (address >= 0xD000 && address < 0xE000)
        gb_memory->wramx[address - 0xD000] = value;
    else if (address >= 0xFE00 && address < 0xFEA0)
        gb_memory->oam[address - 0xFE00] = value;
    else if (address >= 0xFF00 && address < 0xFF80)
        gb_memory->io_regs[address - 0xFF00] = value;
    else if (address >= 0xFF80 && address < 0xFFFF)
        gb_memory->hram[address - 0xFF80] = value;
    else if (address == 0xFFFF)
        *gb_memory->ie_reg = value;
}

void free_memory(void)
{
    // Free all allocated memory sections
    free(gb_memory->rom0);
    free(gb_memory->romx);
    free(gb_memory->vram);
    free(gb_memory->sram);
    free(gb_memory->wram0);
    free(gb_memory->wramx);
    free(gb_memory->oam);
    free(gb_memory->io_regs);
    free(gb_memory->hram);
    free(gb_memory->ie_reg);
    free(gb_memory);
}
