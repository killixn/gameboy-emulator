// Implements the Game Boy CPU instructions and operations.

#include "cpu.h"

#include "src/instruct.h"

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
    // TODO
    switch (opcode)
    { // opcode for load 8bits value in register
    case 0x06:
        ld_8bits(&cpu_register.BC.reg8.high,
                 memory_read(cpu_register.PC.reg16++));
        break;
    case 0x0E:
        ld_8bits(&cpu_register.BC.reg8.low,
                 memory_read(cpu_register.PC.reg16++));
        break;
    case 0x16:
        ld_8bits(&cpu_register.DE.reg8.high,
                 memory_read(cpu_register.PC.reg16++));
        break;
    case 0x1E:
        ld_8bits(&cpu_register.DE.reg8.low,
                 memory_read(cpu_register.PC.reg16++));
        break;
    case 0x26:
        ld_8bits(&cpu_register.HL.reg8.high,
                 memory_read(cpu_register.PC.reg16++));
        break;
    case 0x2E:
        ld_8bits(&cpu_register.HL.reg8.low,
                 memory_read(cpu_register.PC.reg16++));
        break;

        // opcode for load 8bits register into other register
    case 0x7F: // register A
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.AF.reg8.high);
        break;
    case 0x78:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.BC.reg8.high);
        break;
    case 0x79:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.BC.reg8.low);
        break;
    case 0x7A:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.DE.reg8.high);
        break;
    case 0x7B:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.DE.reg8.low);
        break;
    case 0x7C:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.HL.reg8.high);
        break;
    case 0x7D:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.HL.reg8.low);
        break;
    case 0x7E:
        ld_r1_r2_8bits(&cpu_register.AF.reg8.high, cpu_register.HL.reg16);
        break;

    case 0x40: // register B
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.BC.reg8.high);
        break;
    case 0x41:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.BC.reg8.low);
        break;
    case 0x42:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.DE.reg8.high);
        break;
    case 0x43:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.DE.reg8.low);
        break;
    case 0x44:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.HL.reg8.high);
        break;
    case 0x45:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.HL.reg8.low);
        break;
    case 0x46:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.high, cpu_register.HL.reg16);
        break;

    case 0x48: // register C
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.BC.reg8.high);
        break;
    case 0x49:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.BC.reg8.low);
        break;
    case 0x4A:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.DE.reg8.high);
        break;
    case 0x4B:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.DE.reg8.low);
        break;
    case 0x4C:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.HL.reg8.high);
        break;
    case 0x4D:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.HL.reg8.low);
        break;
    case 0x4E:
        ld_r1_r2_8bits(&cpu_register.BC.reg8.low, cpu_register.HL.reg16);
        break;

    case 0x50: // register D
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.BC.reg8.high);
        break;
    case 0x51:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.BC.reg8.low);
        break;
    case 0x52:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.DE.reg8.high);
        break;
    case 0x53:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.DE.reg8.low);
        break;
    case 0x54:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.HL.reg8.high);
        break;
    case 0x55:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.HL.reg8.low);
        break;
    case 0x56:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.high, cpu_register.HL.reg16);
        break;

    case 0x58: // register E
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.BC.reg8.high);
        break;
    case 0x59:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.BC.reg8.low);
        break;
    case 0x5A:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.DE.reg8.high);
        break;
    case 0x5B:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.DE.reg8.low);
        break;
    case 0x5C:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.HL.reg8.high);
        break;
    case 0x5D:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.HL.reg8.low);
        break;
    case 0x5E:
        ld_r1_r2_8bits(&cpu_register.DE.reg8.low, cpu_register.HL.reg16);
        break;

    case 0x60: // register H
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.BC.reg8.high);
        break;
    case 0x61:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.BC.reg8.low);
        break;
    case 0x62:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.DE.reg8.high);
        break;
    case 0x63:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.DE.reg8.low);
        break;
    case 0x64:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.HL.reg8.high);
        break;
    case 0x65:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.HL.reg8.low);
        break;
    case 0x66:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.high, cpu_register.HL.reg16);
        break;

    case 0x68: // register L
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.BC.reg8.high);
        break;
    case 0x69:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.BC.reg8.low);
        break;
    case 0x6A:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.DE.reg8.high);
        break;
    case 0x6B:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.DE.reg8.low);
        break;
    case 0x6C:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.HL.reg8.high);
        break;
    case 0x6D:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.HL.reg8.low);
        break;
    case 0x6E:
        ld_r1_r2_8bits(&cpu_register.HL.reg8.low, cpu_register.HL.reg16);
        break;

    case 0x70: // register L
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.BC.reg8.high);
        break;
    case 0x71:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.BC.reg8.low);
        break;
    case 0x72:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.DE.reg8.high);
        break;
    case 0x73:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.DE.reg8.low);
        break;
    case 0x74:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.HL.reg8.high);
        break;
    case 0x75:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.HL.reg8.low);
        break;
    case 0x36:
        ld_r1_r2_16bits(&cpu_register.HL.reg16, cpu_register.PC.reg16);
        break;

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
