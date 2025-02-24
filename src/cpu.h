#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>

// Group two 8-bit registers to form 16-bit pairs
typedef union
{
    uint16_t reg16; // Registrer 16 bits
    struct
    {
        uint8_t low; // 8 firt bits
        uint8_t high; // 8 last bits
    } reg8;
} Register;

// CPU structure with all registers and flags
struct cpu_register
{
    Register AF;
    Register BC;
    Register DE;
    Register HL;
    Register SP; // Stack pointer
    Register PC; // Programme counter
    u_int8_t flags_register;
};

void cpu();
void init_cpu();

#endif /* !CPU_H */
