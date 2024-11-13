#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>

struct memory
{
    unsigned char *rom0; //    Non-switchable ROM Bank
    unsigned char *romx; //    Switchable ROM bank
    unsigned char *vram; //    Video RAM, switchable (0-1) in GBC mode
    unsigned char *sram; //    External RAM in cartridge, often battery buffered
    unsigned char *wram0; //   Work RAM
    unsigned char *wramx; //   Work RAM, switchable (1-7) in GBC mode
    unsigned char *oam; //     (Object Attribute Table) Sprite information table
    unsigned char *io_regs; // I/O registers are mapped here
    unsigned char *hram; //    Internal CPU RAM
    unsigned char *ie_reg; //  Interrupt enable flags
};

int memory_init(void);
unsigned char memory_read(struct memory *gb_memory, size_t address);
void memory_write(struct memory *gb_memory, size_t address, size_t value);
void free_memory(void);

#endif /* !MEMORY_H */
