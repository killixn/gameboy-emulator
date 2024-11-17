// Implements the Game Boy CPU instructions and operations.

#include "cpu.h"

#include "instruct.h"

// get the global variable rom
extern struct rom rom;

// init static cpu register
static struct cpu_register cpu_register;

// function to execute all the opcode
void exec_opcode(uint8_t opcode)
{
#ifdef DEBUG
    printf("Executing opcode: 0x%02X\n", opcode);
#endif
    switch (opcode)
    { // opcode for load 8bits value in register
    case 0x06:
        ld(&cpu_register.BC.reg8.high,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;
    case 0x0E:
        ld(&cpu_register.BC.reg8.low,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;
    case 0x16:
        ld(&cpu_register.DE.reg8.high,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;
    case 0x1E:
        ld(&cpu_register.DE.reg8.low,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;
    case 0x26:
        ld(&cpu_register.HL.reg8.high,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;
    case 0x2E:
        ld(&cpu_register.HL.reg8.low,
           (uint8_t)memory_read(cpu_register.PC.reg16++));
        break;

    // opcode for load 8bits register into other register
    case 0x7F: // register A
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.AF.reg8.high);
        break;
    case 0x78:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.BC.reg8.high);
        break;
    case 0x79:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.BC.reg8.low);
        break;
    case 0x7A:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.DE.reg8.high);
        break;
    case 0x7B:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.DE.reg8.low);
        break;
    case 0x7C:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.HL.reg8.high);
        break;
    case 0x7D:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.HL.reg8.low);
        break;
    case 0x7E:
        ld_r1_r2(&cpu_register.AF.reg8.high, 8, cpu_register.HL.reg16);
        break;

    case 0x40: // register B
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.BC.reg8.high);
        break;
    case 0x41:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.BC.reg8.low);
        break;
    case 0x42:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.DE.reg8.high);
        break;
    case 0x43:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.DE.reg8.low);
        break;
    case 0x44:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.HL.reg8.high);
        break;
    case 0x45:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.HL.reg8.low);
        break;
    case 0x46:
        ld_r1_r2(&cpu_register.BC.reg8.high, 8, cpu_register.HL.reg16);
        break;

    case 0x48: // register C
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.BC.reg8.high);
        break;
    case 0x49:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.BC.reg8.low);
        break;
    case 0x4A:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.DE.reg8.high);
        break;
    case 0x4B:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.DE.reg8.low);
        break;
    case 0x4C:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.HL.reg8.high);
        break;
    case 0x4D:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.HL.reg8.low);
        break;
    case 0x4E:
        ld_r1_r2(&cpu_register.BC.reg8.low, 8, cpu_register.HL.reg16);
        break;

    case 0x50: // register D
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.BC.reg8.high);
        break;
    case 0x51:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.BC.reg8.low);
        break;
    case 0x52:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.DE.reg8.high);
        break;
    case 0x53:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.DE.reg8.low);
        break;
    case 0x54:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.HL.reg8.high);
        break;
    case 0x55:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.HL.reg8.low);
        break;
    case 0x56:
        ld_r1_r2(&cpu_register.DE.reg8.high, 8, cpu_register.HL.reg16);
        break;

    case 0x58: // register E
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.BC.reg8.high);
        break;
    case 0x59:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.BC.reg8.low);
        break;
    case 0x5A:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.DE.reg8.high);
        break;
    case 0x5B:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.DE.reg8.low);
        break;
    case 0x5C:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.HL.reg8.high);
        break;
    case 0x5D:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.HL.reg8.low);
        break;
    case 0x5E:
        ld_r1_r2(&cpu_register.DE.reg8.low, 8, cpu_register.HL.reg16);
        break;

    case 0x60: // register H
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.BC.reg8.high);
        break;
    case 0x61:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.BC.reg8.low);
        break;
    case 0x62:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.DE.reg8.high);
        break;
    case 0x63:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.DE.reg8.low);
        break;
    case 0x64:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.HL.reg8.high);
        break;
    case 0x65:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.HL.reg8.low);
        break;
    case 0x66:
        ld_r1_r2(&cpu_register.HL.reg8.high, 8, cpu_register.HL.reg16);
        break;

    case 0x68: // register L
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.BC.reg8.high);
        break;
    case 0x69:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.BC.reg8.low);
        break;
    case 0x6A:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.DE.reg8.high);
        break;
    case 0x6B:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.DE.reg8.low);
        break;
    case 0x6C:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.HL.reg8.high);
        break;
    case 0x6D:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.HL.reg8.low);
        break;
    case 0x6E:
        ld_r1_r2(&cpu_register.HL.reg8.low, 8, cpu_register.HL.reg16);
        break;

    case 0x70: // register L
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.BC.reg8.high);
        break;
    case 0x71:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.BC.reg8.low);
        break;
    case 0x72:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.DE.reg8.high);
        break;
    case 0x73:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.DE.reg8.low);
        break;
    case 0x74:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.HL.reg8.high);
        break;
    case 0x75:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.HL.reg8.low);
        break;
    case 0x36:
        ld_r1_r2(&cpu_register.HL.reg16, 16, cpu_register.PC.reg16);
        break;

    // DAA (page 95)
    case 0x27:
        dda(&cpu_register.AF.reg8.high, &cpu_register.flags_register);
        break;

    // CPL (page 95)
    case 0x2F:
        cpl(&cpu_register.AF.reg8.high, &cpu_register.flags_register);
        break;

    // CCF (page 96)
    case 0x3F:
        ccf(&cpu_register.flags_register);
        break;

    // SCF (page 96)
    case 0x37:
        scf(&cpu_register.flags_register);
        break;

    // NOP (page 97)
    case 0x00:
        nop();
        break;

    // HALT (page 97)
    case 0x76:
        halt();
        break;

    // STOP (page 97)
    // TODO: opcode -> 10 00
    case 0x10:
        stop();
        break;

    // DI (page 98)
    // TODO:
    case 0xF3:
        di();
        break;

    // EI (page 98)
    // TODO:
    case 0xFB:
        ei();
        break;

    // RLCA (page 99)
    case 0x07:
        rlc(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;

    // RLA (page 99)
    case 0x17:
        rl(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;

    // RRCA (page 100)
    case 0x0F:
        rrc(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;

    // RRA (page 100)
    case 0x1F:
        rr(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;

    // JP nn (page 111)
    case 0xC3:
        jp(&cpu_register.PC.reg16);
        break;

    // JP cc, nn (page 113)
    case 0xC2: // JP NZ,nn
        if ((cpu_register.flags_register & 0x80) == 0) // Z flag = 0
            jp(&cpu_register.PC.reg16);
        break;

    case 0xCA: // JP Z,nn
        if ((cpu_register.flags_register & 0x80) != 0) // Z flag = 1
            jp(&cpu_register.PC.reg16);
        break;

    case 0xD2: // JP NC,nn
        if ((cpu_register.flags_register & 0x10) == 0) // C flag = 0
            jp(&cpu_register.PC.reg16);
        break;

    case 0xDA: // JP C,nn
        if ((cpu_register.flags_register & 0x10) != 0) // C flag = 1
            jp(&cpu_register.PC.reg16);
        break;

    // JP (HL) (page 112)
    case 0xE9:
        jp_hl(&cpu_register.PC.reg16, &cpu_register.HL.reg16);
        break;

    // JR n (page 112)
    case 0x18:
        jr(&cpu_register.PC.reg16);
        break;

    // JR cc,n (page 114)
    case 0x20: // JR NZ,n
        if ((cpu_register.flags_register & 0x80) == 0) // Z flag = 0 (NZ)
            jr(&cpu_register.PC.reg16);
        break;

    case 0x28: // JR Z,n
        if ((cpu_register.flags_register & 0x80) != 0) // Z flag = 1 (Z)
            jr(&cpu_register.PC.reg16);
        break;

    case 0x30: // JR NC,n
        if ((cpu_register.flags_register & 0x10) == 0) // C flag = 0 (NC)
            jr(&cpu_register.PC.reg16);
        break;

    case 0x38: // JR C,n
        if ((cpu_register.flags_register & 0x10) != 0) // C flag = 1 (C)
            jr(&cpu_register.PC.reg16);
        break;

    // CALL nn (page 114)
    case 0xCD:
        call(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;

    // CALL cc,nn (page 115)
    case 0xC4:
        if ((cpu_register.flags_register & 0x80) == 0) // Z flag = 0 (NZ)
            call(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xCC:
        if ((cpu_register.flags_register & 0x80) != 0) // Z flag = 1 (Z)
            call(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xD4:
        if ((cpu_register.flags_register & 0x10) == 0) // C flag = 0 (NC)
            call(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xDC:
        if ((cpu_register.flags_register & 0x10) != 0) // C flag = 1 (C)
            call(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;

    // RST n (page 116)
    case 0xC7:
    case 0xCF:
    case 0xD7:
    case 0xDF:
    case 0xE7:
    case 0xEF:
    case 0xF7:
    case 0xFF:
        rst(opcode, &cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;

    // RET (page 117)
    case 0xC9:
        ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;

    // RET cc (page 117)
    case 0xC0:
        if ((cpu_register.flags_register & 0x80) == 0) // Z flag = 0 (NZ)
            ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xC8:
        if ((cpu_register.flags_register & 0x80) != 0) // Z flag = 1 (Z)
            ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xD0:
        if ((cpu_register.flags_register & 0x10) == 0) // C flag = 0 (NC)
            ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;
    case 0xD8:
        if ((cpu_register.flags_register & 0x10) != 0) // C flag = 1 (C)
            ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        break;

    // RETI (page 118)
    case 0xD9:
        ret(&cpu_register.PC.reg16, &cpu_register.SP.reg16);
        ei();
        break;

    case 0xCB: {
        uint8_t cb_opcode = memory_read(
            cpu_register.PC.reg16++); // Recover next opcode following 0xCB
        uint8_t val = (cb_opcode >> 3) & 0x07; // Extract op value (bits 3-5)
        uint8_t r_index = cb_opcode & 0x07; // Extract register index (bits 0-2)

        void *registers[8] = {
            &cpu_register.BC.reg8.high, &cpu_register.BC.reg8.low,
            &cpu_register.DE.reg8.high, &cpu_register.DE.reg8.low,
            &cpu_register.HL.reg8.high, &cpu_register.HL.reg8.low,
            &cpu_register.HL.reg16,     &cpu_register.AF.reg8.high
        }; // Define a lookup table of pointers to registers

        uint8_t reg_size = (r_index == 6) ? 16 : 8; // Get register size
        void *reg_ptr = registers[r_index]; // Get ptr to selected register

        switch (cb_opcode & 0xF8)
        {
        case 0x30: // SWAP n (page 94)
            swap(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x00: // RLC n (page 101)
            rlc(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x10: // RL n (page 102)
            rl(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x08: // RRC n (page 103)
            rrc(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x18: // RR n (page 104)
            rr(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x20: // SLA n (page 105)
            sla(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x28: // SRA n (page 106)
            sra(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x38: // SRL n (page 107)
            srl(reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0x40: // BIT b,r (page 108)
            bit(val, reg_ptr, reg_size, &cpu_register.flags_register);
            break;
        case 0xC0: // SET b,r (page 109)
            set(val, reg_ptr, reg_size);
            break;
        case 0x80: // RES b,r (page 110)
            res(val, reg_ptr, reg_size);
            break;
        default:
            fprintf(stderr, "error: opcode not recognised\n");
            abort(); // if opcode is not recognised, stop the programme
        }
    }

    default:
        fprintf(stderr, "error: opcode not recognised\n");
        abort(); // if opcode is not recognised, stop the programme
    }
}

void init_cpu()
{
    cpu_register.AF.reg16 = 0;
    cpu_register.BC.reg16 = 0;
    cpu_register.DE.reg16 = 0;
    cpu_register.HL.reg16 = 0;
    cpu_register.SP.reg16 = 0;
    cpu_register.PC.reg16 = 0x100;
    cpu_register.flags_register = 0;
}

// main cpu fonction
void cpu()
{
    // get and exec next opcode from the rom
    uint8_t opcode = memory_read(cpu_register.PC.reg16++);
    exec_opcode(opcode);
}
