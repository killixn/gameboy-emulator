#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>

#include "memory.h"

// group two 8-bit registers to form 16-bit pairs
typedef union
{
    uint16_t reg16; // registrer 16 bits
    struct
    {
        uint8_t low; // 8 firt bits
        uint8_t high; // 8 last bits
    } reg8;
} Register;

// cpu structure with all registers and flags
struct cpu_register
{
    Register AF;
    Register BC;
    Register DE;
    Register HL;
    Register SP; // stack pointer
    Register PC; // programme counter
    u_int8_t flags_register;
};

void cpu();
void init_cpu();

#endif /* !CPU_H */
