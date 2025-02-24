#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct memory
{
    uint8_t *rom0; //    Non-switchable ROM Bank
    uint8_t *romx; //    Switchable ROM bank
    uint8_t *vram; //    Video RAM, switchable (0-1) in GBC mode
    uint8_t *sram; //    External RAM in cartridge, often battery buffered
    uint8_t *wram0; //   Work RAM
    uint8_t *wramx; //   Work RAM, switchable (1-7) in GBC mode
    uint8_t *oam; //     (Object Attribute Table) Sprite information table
    uint8_t *io_regs; // I/O registers are mapped here
    uint8_t *hram; //    Internal CPU RAM
    uint8_t *ie_reg; //  Interrupt enable flags
};

int memory_init(void);
uint8_t memory_read(size_t address);
void memory_write(size_t address, u_int8_t value);
void free_memory(void);

#endif /* !MEMORY_H */
