// Implements the Game Boy CPU instructions and operations.

#include "cpu.h"

// get the global variable rom
extern struct rom rom;

// init static cpu register
static struct cpu_register cpu_register;

// function to execute all the opcode
void exec_opcode(struct cpu_register *cpu_register, uint8_t opcode)
{
    // TODO
    switch (opcode)
    {
    case 0x06:
        cpu_register->BC.reg8.high = cpu_register->PC.reg16;
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
    exec_opcode(&cpu_register, opcode);
}
