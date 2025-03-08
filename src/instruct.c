#include "instruct.h"

#include <stdint.h>
#include <stdio.h>

#include "memory.h"

// LD nn,n (page 65)
void ld(uint8_t *r, uint16_t value)
{
    *r = value; // Put value into r
}

void ld_n(uint8_t *r, uint16_t value)
{
    *r = memory_read(value); // Put value into r
}

void ld_nn(uint16_t *r, uint16_t *pc)
{
    uint16_t nn = memory_read((*pc)++) | (memory_read((*pc)++) << 8);
    *r = nn;
}
// LD r1,r2 (page 66)
void ld_r1_r2(void *r1, uint8_t r2, uint8_t size)
{
    if (size == 8)
    {
        uint8_t *r18 = (uint8_t *)r1;
        *r18 = r2; // Put value r2 into r1
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r1;
        *r16 = r2; // Put value r2 into r1
    }
}

void add(void *r, uint16_t value, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *r8 = (uint8_t *)r;
        *r8 += value; // Add value to r
        if (*r8 == 0)
        {
            *flags |= FLAG_N; // Set N
            *flags &= ~FLAG_H; // Reset H
        }
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r;
        *r16 += value; // Add value to r
        if (*r16 == 0)
        {
            *flags |= FLAG_N; // Set N
            *flags &= ~FLAG_H; // Reset H
        }
    }
}

void adc(uint8_t *r, uint16_t value, uint8_t *flags)
{
    *r += value;
    if (*r == 0)
    {
        *flags |= FLAG_N; // Set N
        *flags &= ~FLAG_H; // Reset H
    }
}

// page (82)
void sub(uint8_t *r, uint16_t value, uint8_t *flags)
{
    if (*r >= value)
        *flags |= FLAG_C; // Set C if borrow from MSB

    *r -= value;
    if (*r == 0)
        *flags |= FLAG_Z; // Set Z
    *flags |= FLAG_N; // Set N
    if (((*r & 0x0F) - 1) >= 0x00)
        *flags |= FLAG_H; // Set H if no borrow from bit 4
}

void sbc(uint8_t *r, uint16_t value, uint8_t *flags)
{
    uint8_t carry = (*flags & FLAG_C) ? 1 : 0;

    if (*r >= value + carry)
        *flags |= FLAG_C; // Set C if borrow from MSB

    *r -= value;
    if (*r == 0)
        *flags |= FLAG_Z; // Set Z
    *flags |= FLAG_N; // Set N
    if (((*r & 0x0F) - 1) >= 0x00)
        *flags |= FLAG_H; // Set H if no borrow from bit 4
}

void funcAnd(uint8_t *r, uint16_t value, uint8_t *flags)
{
    *r = *r & value;

    if (*r == 0)
        *flags |= FLAG_Z; // Set Z

    *flags &= ~FLAG_N; // Reset N pour les opérations logique
    *flags |= FLAG_H; // Set H
    *flags &= ~FLAG_C; // Reset C
}

void funcOr(uint8_t *r, uint16_t value, uint8_t *flags)
{
    *r = *r | value;

    if (*r == 0)
        *flags |= FLAG_Z; // Set Z

    *flags &= ~FLAG_N; // Reset N pour les opérations logique
    *flags &= ~FLAG_H; // Reset H
    *flags &= ~FLAG_C; // Reset C
}

void funcXor(uint8_t *r, uint16_t value, uint8_t *flags)
{
    *r = *r ^ value;

    if (*r == 0)
        *flags |= FLAG_Z; // Set Z

    *flags &= ~FLAG_N; // Reset N pour les opérations logique
    *flags &= ~FLAG_H; // Reset H
    *flags &= ~FLAG_C; // Reset C
}

void funcCp(uint8_t *r, uint16_t value, uint8_t *flags)
{
    uint8_t result = *r - value;

    if (*r == value)
        *flags |= FLAG_Z; // Set Z

    *flags |= FLAG_N; // Set N

    if ((result & 0x0F) > 0x0F)
        *flags |= FLAG_H; // Set H if carry from bit 4

    if (*r < value)
        *flags |= FLAG_C; // Set C
}

void inc(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        (*n8)++;

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        *flags &= ~FLAG_N; // Reset N
        if (((*n8 & 0x0F) + 1) > 0x0F)
            *flags |= FLAG_H; // Set H if carry from bit 3
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        (*n16)++;

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        *flags &= ~FLAG_N; // Reset N
        if (((*n16 & 0x0F) + 1) > 0x0F)
            *flags |= FLAG_H; // Set H if carry from bit 3
    }
}

// DEC n (page 89)
void dec(void *n, uint8_t size, uint8_t *flags)
{
    *flags |= FLAG_N; // set N flag
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        (*n8)--;

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (((*n8 & 0x0F) - 1) < 0x00)
            *flags |= FLAG_H; // Set H if no borrow from bit 4
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        (*n16)--;

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (((*n16 & 0x0F) - 1) < 0x00)
            *flags |= FLAG_H; // Set H if no borrow from bit 4
    }
}

// SWAP n (page 94)
void swap(void *r, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *r8 = (uint8_t *)r;
        *r8 = ((*r8 & 0xF0) >> 4) | ((*r8 & 0x0F) << 4); // Swap up-low nibles

        *flags = 0; // Set all flag to 0
        if (*r8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r;
        *r16 = ((*r16 & 0xFF00) >> 8)
            | ((*r16 & 0x00FF) << 8); // Swap up-low nibles

        *flags = 0; // Set all flag to 0
        if (*r16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
    }
}

// DAA (page 95)
void dda(uint8_t *a, uint8_t *flags)
{
    uint8_t old_cr =
        (*flags & FLAG_C) >> 4; // Recover the old Carry flag (bit 4)

    if ((*a & 0x0F) > 9 || (*flags & FLAG_H))
        *a += 0x06; // Add 0x06 to adjust the lower nibble

    if (*a > 0x99 || old_cr)
    {
        *a += 0x60; // Add 0x60 to adjust the higher nibble
        *flags |= FLAG_C; // Set C flag if A is greater than 99 or carry is set
    }

    if (*a == 0)
        *flags |= FLAG_Z; // Set Z if a is 0
    *flags &= ~FLAG_H; // Reset H
}

// CPL (page 95)
void cpl(uint8_t *a, uint8_t *flags)
{
    *a = ~(*a); // Flip all A bits
    *flags |= FLAG_N; // Set N
    *flags |= FLAG_H; // Set H
}

// CCF (page 96)
void ccf(uint8_t *flags)
{
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
    *flags ^= FLAG_C; // Complement C
}

// SCF (page 96)
void scf(uint8_t *flags)
{
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
    *flags |= FLAG_C; // Set C
}

// NOP (page 97)
void nop(void)
{
    return; // No operation
}

// HALT (page 97)
void halt(void)
{
    return; // Power down CPU until an interrupt occurs
}

// STOP (page 97)
void stop(void)
{
    return; // Halt CPU-LCD display until button pressed
}

// DI (page 98)
void di(void)
{
    // TODO:
    return; // Disable interrupts
}

// EI (page 98)
void ei(void)
{
    // TODO:
    return; // Enable interrupts
}

// RLC n (page 101)
void rlc(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t msb = *n8 >> 7; // Recover MSB (bit 7)

        *n8 = (*n8 << 1) | msb; // Rotate n left, put old MSB in bit 0

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t msb = *n16 >> 15; // Recover MSB (bit 15)

        *n16 = (*n16 << 1) | msb; // Rotate n left, put old MSB in bit 0

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB was 1
    }
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
}

// RL n (page 101)
void rl(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t msb = *n8 >> 7; // Recover MSB (bit 7)

        uint8_t cr =
            (*flags & FLAG_C) >> 4; // Recover the current Carry flag (bit 4)
        *n8 = (*n8 << 1)
            | cr; // Rotate n left through Carry, put old MSB in bit 0

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t msb = *n16 >> 15; // Recover MSB (bit 15)

        uint8_t cr =
            (*flags & FLAG_C) >> 4; // Recover the current Carry flag (bit 4)
        *n16 = (*n16 << 1)
            | cr; // Rotate n left through Carry, put old MSB in bit 0

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB is 1
    }
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
}

// RRC n (page 102)
void rrc(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t lsb = *n8 & 1; // Recover LSB (bit 0)

        *n8 =
            (*n8 >> 1) | (lsb << 7); // Rotate n right, put the old LSB in bit 7

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t lsb = *n16 & 1; // Recover LSB (bit 0)

        *n16 = (*n16 >> 1)
            | (lsb << 15); // Rotate n right, put the old LSB in bit 15

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
}

// RR n (page 102)
void rr(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t lsb = *n8 & 1; // Recover LSB (bit 0)

        uint8_t cr =
            (*flags & FLAG_C) >> 4; // Recover the current Carry flag (bit 4)
        *n8 = (*n8 >> 1)
            | (cr << 7); // Rotate n right through Carry, put old LSB in bit 7

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t lsb = *n16 & 1; // Recover LSB (bit 0)

        uint16_t cr =
            (*flags & FLAG_C) >> 4; // Recover the current Carry flag (bit 4)
        *n16 = (*n16 >> 1) | (cr << 15); // Rotate n right through Carry,
                                         // put old LSB in bit 15

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
}

// SLA n (page 105)
void sla(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t msb = *n8 >> 7; // Recover MSB (bit 7)

        *n8 = (*n8 << 1); // Shift n left

        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t msb = *n16 >> 15; // Recover MSB (bit 15)

        *n16 = (*n16 << 1); // Shift n left

        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (msb)
            *flags |= FLAG_C; // Set C if MSB was 1
    }
    *flags &= ~FLAG_N; // Reset N
    *flags &= ~FLAG_H; // Reset H
}

// SRA n (Shift Right Arithmetic)
void sra(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t lsb = *n8 & 1; // Recover LSB (bit 0)
        uint8_t msb = *n8 >> 7; // Preserve MSB (bit 7)

        *n8 = (*n8 >> 1) | msb; // Shift right, keep MSB unchanged

        *flags = 0; // Reset all flags
        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t lsb = *n16 & 1; // Recover LSB (bit 0)
        uint16_t msb = *n16 >> 15; // Preserve MSB (bit 15)

        *n16 = (*n16 >> 1) | msb; // Shift right, keep MSB unchanged

        *flags = 0; // Reset all flags
        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
}

// SRL n (Shift Right Logical)
void srl(void *n, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *n8 = (uint8_t *)n;
        uint8_t lsb = *n8 & 1; // Recover LSB (bit 0)

        *n8 = (*n8 >> 1); // Shift right, MSB becomes 0

        *flags = 0; // Reset all flags
        if (*n8 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
    else if (size == 16)
    {
        uint16_t *n16 = (uint16_t *)n;
        uint16_t lsb = *n16 & 1; // Recover LSB (bit 0)

        *n16 = (*n16 >> 1); // Shift right, MSB becomes 0

        *flags = 0; // Reset all flags
        if (*n16 == 0)
            *flags |= FLAG_Z; // Set Z if result is 0
        if (lsb)
            *flags |= FLAG_C; // Set C if LSB was 1
    }
}

// BIT b,r (page 108)
void bit(uint8_t b, void *r, uint8_t size, uint8_t *flags)
{
    if (size == 8)
    {
        uint8_t *r8 = (uint8_t *)r;
        ((*r8 >> b) & 1)
            ? (*flags &= ~FLAG_Z)
            : (*flags |= FLAG_Z); // Set Z if bit b of register r is 0
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r;
        ((*r16 >> b) & 1)
            ? (*flags &= ~FLAG_Z)
            : (*flags |= FLAG_Z); // Set Z if bit b of register r is 0
    }
    *flags &= ~FLAG_N; // Reset N
    *flags |= FLAG_H; // Set H
}

// SET b,r (page 109)
void set(uint8_t b, void *r, uint8_t size)
{
    if (size == 8)
    {
        uint8_t *r8 = (uint8_t *)r;
        *r8 |= 1 << b; // Set bit b in register r
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r;
        *r16 |= 1 << b; // Set bit b in register r
    }
}

// RES b,r (page 110)
void res(uint8_t b, void *r, uint8_t size)
{
    if (size == 8)
    {
        uint8_t *r8 = (uint8_t *)r;
        *r8 &= ~(1 << b); // Reset bit b in register r
    }
    else if (size == 16)
    {
        uint16_t *r16 = (uint16_t *)r;
        *r16 &= ~(1 << b); // Reset bit b in register r
    }
}

// JP nn (page 111)
// JP cc,nn (page 111)
void jp(uint16_t *pc)
{
    uint16_t nn = memory_read((*pc)++) | (memory_read((*pc)++) << 8);
    *pc = nn;
}

// JP (HL) (page 112)
void jp_hl(uint16_t *pc, uint16_t *hl)
{
    *pc = *hl; // Jump to address contained in HL
}

// JR n (page 112)
// JR cc,n (page 113)
void jr(uint16_t *pc)
{
    uint8_t n = (uint8_t)memory_read((*pc)++);
    *pc += n;
}

// CALL nn (page 114)
// CALL cc,nn (page 115)
void call(uint16_t *pc, uint16_t *sp)
{
    uint16_t nn = memory_read((*pc)++)
        | (memory_read((*pc)++) << 8); // Recover LSB, then MSB

    *sp -= 1;
    memory_write(*sp, (*pc >> 8) & 0xFF); // Store MSB

    *sp -= 1;
    memory_write(*sp, *pc & 0xFF); // Store LSB

    *pc = nn; // Jump to address nn
}

// RST n (page 116)
void rst(uint8_t opcode, uint16_t *pc, uint16_t *sp)
{
    *sp -= 1;
    memory_write(*sp, (*pc >> 8) & 0xFF); // Store MSB

    *sp -= 1;
    memory_write(*sp, *pc & 0xFF); // Store LSB

    *pc = 0x0000 + (opcode & 0x38);
}

// RET (page 117)
// RET cc (page 117)
// RETI (page 118)
void ret(uint16_t *pc, uint16_t *sp)
{
    uint8_t lsb = memory_read(*sp); // Store LSB
    *sp += 1;
    uint8_t msb = memory_read(*sp); // Store MSB
    *sp += 1;

    *pc = (msb << 8) | lsb; // Jump to address nn
}
