// Implements the Game Boy CPU instructions and operations.

#include "cpu.h"

#include "instruct.h"

// get the global variable rom
extern struct rom rom;

// init static cpu register
static struct cpu_register cpu_register;

// function to execute all the opcode
void exec_opcode(uint16_t opcode)
{
#ifdef DEBUG
    printf("Executing opcode: 0x%04X\n", opcode);
#endif
    // TODO
    switch (opcode)
    { // opcode for load 8bits value in register
    case 0x06:
        ld(&cpu_register.BC.reg8.high, memory_read(cpu_register.PC.reg16++));
        break;
    case 0x0E:
        ld(&cpu_register.BC.reg8.low, memory_read(cpu_register.PC.reg16++));
        break;
    case 0x16:
        ld(&cpu_register.DE.reg8.high, memory_read(cpu_register.PC.reg16++));
        break;
    case 0x1E:
        ld(&cpu_register.DE.reg8.low, memory_read(cpu_register.PC.reg16++));
        break;
    case 0x26:
        ld(&cpu_register.HL.reg8.high, memory_read(cpu_register.PC.reg16++));
        break;
    case 0x2E:
        ld(&cpu_register.HL.reg8.low, memory_read(cpu_register.PC.reg16++));
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

    // SWAP n (page 94)
    case 0xCB37:
        swap(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB30:
        swap(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB31:
        swap(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB32:
        swap(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB33:
        swap(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB34:
        swap(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB35:
        swap(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB36:
        swap(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
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
    case 0x1000:
        stop();
        break;

    // DI (page 98)
    case 0xF3:
        // TODO:
        di();
        break;

    // EI (page 98)
    case 0xFB:
        // TODO:
        ei();
        break;

    // RLCA (page 99)
    case 0x07:
    // RLC n (page 101)
    case 0xCB07:
        rlc(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB00:
        rlc(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB01:
        rlc(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB02:
        rlc(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB03:
        rlc(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB04:
        rlc(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB05:
        rlc(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB06:
        rlc(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // RLA (page 99)
    case 0x17:
    // RL n (page 102)
    case 0xCB17:
        rl(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB10:
        rl(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB11:
        rl(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB12:
        rl(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB13:
        rl(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB14:
        rl(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB15:
        rl(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB16:
        rl(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // RRCA (page 100)
    case 0x0F:
    // RRC n (page 103)
    case 0xCB0F:
        rrc(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB08:
        rrc(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB09:
        rrc(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB0A:
        rrc(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB0B:
        rrc(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB0C:
        rrc(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB0D:
        rrc(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB0E:
        rrc(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // RRA (page 100)
    case 0x1F:
    // RR n (page 104)
    case 0xCB1F:
        rr(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB18:
        rr(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB19:
        rr(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB1A:
        rr(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB1B:
        rr(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB1C:
        rr(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB1D:
        rr(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB1E:
        rr(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // SLA n (page 105)
    case 0xCB27:
        sla(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB20:
        sla(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB21:
        sla(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB22:
        sla(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB23:
        sla(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB24:
        sla(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB25:
        sla(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB26:
        sla(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // SRA n (page 106)
    case 0xCB2F:
        sra(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB28:
        sra(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB29:
        sra(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB2A:
        sra(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB2B:
        sra(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB2C:
        sra(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB2D:
        sra(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB2E:
        sra(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // SRL n (page 107)
    case 0xCB3F:
        srl(&cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB38:
        srl(&cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB39:
        srl(&cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB3A:
        srl(&cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB3B:
        srl(&cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB3C:
        srl(&cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB3D:
        srl(&cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB3E:
        srl(&cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // BIT b,r (page 108)
    case 0xCB47:
        bit(101, &cpu_register.AF.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB40:
        bit(101, &cpu_register.BC.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB41:
        bit(101, &cpu_register.BC.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB42:
        bit(101, &cpu_register.DE.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB43:
        bit(101, &cpu_register.DE.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB44:
        bit(101, &cpu_register.HL.reg8.high, 8, &cpu_register.flags_register);
        break;
    case 0xCB45:
        bit(101, &cpu_register.HL.reg8.low, 8, &cpu_register.flags_register);
        break;
    case 0xCB46:
        bit(101, &cpu_register.HL.reg16, 16, &cpu_register.flags_register);
        break;

    // SET b,r (page 109)
    case 0xCBC7:
        set(101, &cpu_register.AF.reg8.high, 8);
        break;
    case 0xCBC0:
        set(101, &cpu_register.BC.reg8.high, 8);
        break;
    case 0xCBC1:
        set(101, &cpu_register.BC.reg8.low, 8);
        break;
    case 0xCBC2:
        set(101, &cpu_register.DE.reg8.high, 8);
        break;
    case 0xCBC3:
        set(101, &cpu_register.DE.reg8.low, 8);
        break;
    case 0xCBC4:
        set(101, &cpu_register.HL.reg8.high, 8);
        break;
    case 0xCBC5:
        set(101, &cpu_register.HL.reg8.low, 8);
        break;
    case 0xCBC6:
        set(101, &cpu_register.HL.reg16, 16);
        break;

    // RES b,r (page 110)
    case 0xCB87:
        res(101, &cpu_register.AF.reg8.high, 8);
        break;
    case 0xCB80:
        res(101, &cpu_register.BC.reg8.high, 8);
        break;
    case 0xCB81:
        res(101, &cpu_register.BC.reg8.low, 8);
        break;
    case 0xCB82:
        res(101, &cpu_register.DE.reg8.high, 8);
        break;
    case 0xCB83:
        res(101, &cpu_register.DE.reg8.low, 8);
        break;
    case 0xCB84:
        res(101, &cpu_register.HL.reg8.high, 8);
        break;
    case 0xCB85:
        res(101, &cpu_register.HL.reg8.low, 8);
        break;
    case 0xCB86:
        res(101, &cpu_register.HL.reg16, 16);
        break;

    // JP nn (page 111)
    case 0xC3:
        break;

    // JP cc,nn (page 111)
    case 0xC2:
        break;
    case 0xCA:
        break;
    case 0xD2:
        break;
    case 0xDA:
        break;

    // JP (HL) (page 112)
    case 0xE9:
        jp_hl(&cpu_register.PC.reg16, &cpu_register.HL.reg16);
        break;

    // JR n (page 112)
    case 0x18:
        break;

    // JR cc,n (page 113)
    case 0x20:
        break;
    case 0x28:
        break;
    case 0x30:
        break;
    case 0x38:
        break;

    // CALL nn (page 114)
    case 0xCD:
        break;

    // CALL cc,nn (page 115)
    case 0xC4:
        break;
    case 0xCC:
        break;
    case 0xD4:
        break;
    case 0xDC:
        break;

    // RST n (page 116)
    case 0xC7:
        break;
    case 0xCF:
        break;
    case 0xD7:
        break;
    case 0xDF:
        break;
    case 0xE7:
        break;
    case 0xEF:
        break;
    case 0xF7:
        break;
    case 0xFF:
        break;

    // RET (page 117)
    case 0xC9:
        break;

    // RET cc (page 117)
    case 0xC0:
        break;
    case 0xC8:
        break;
    case 0xD0:
        break;
    case 0xD8:
        break;

    // RETI (page 118)
    case 0xD9:
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
