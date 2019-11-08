#include "instructionUtil.h"
#include "machine.h"

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * Execute instruction given
 * Returns change in pc
 */
int32_t runInstruction(uint32_t instruction)
{
    int32_t *reg = parseRegisters(instruction);
    int32_t instructionIndex = findInstruction(instruction);

    switch (instructionIndex)
    {
        case ADD: // rd = rn + rm
        {  
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t rm = reg[2];
            machineState.registers[rd] = machineState.registers[rn] + machineState.registers[rm];
            return 1;
        }
        case ADDI: // rd = rn + #im
        {
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t im = reg[2];
            machineState.registers[rd] = machineState.registers[rn] + im;
            return 1;
        }
        case AND: // AND
        {
            return 1;
        }
        case ANDI: // ANDI
        {
            return 1;
        }
        case B: // B
        {
            int32_t adr = reg[0];
            return adr;
        }
        case Bcond: // Bcond
        {
            int32_t rd = reg[0];
            int32_t adr = reg[1];
            if (machineState.conditionRegisters[rd])
            {
                return adr;
            }
            else
            {
                return 1;
            }
        }
        case BL: // BL
        {
            int32_t adr = reg[0];
            machineState.registers[30] = machineState.pc + 1; // X30 = LR
            return adr;
        }
        case BR: // BR
        {
            int32_t rd = reg[0];
            return machineState.registers[30] - machineState.pc; // X30 = LR
        }
        case CBNZ: // CBNZ
        {
            int32_t rd = reg[0];
            int32_t adr = reg[1];
            return machineState.registers[rd] != 0 ? adr : 1;
        }
        case CBZ: // CBZ
        {
            int32_t rd = reg[0];
            int32_t adr = reg[1];
            return machineState.registers[rd] == 0 ? adr : 1;
        }
        case DUMP: // Prints registers, memory, and stack to stdout
        {
            printDump();
            return 1;
        }
        case EOR: // EOR
            return 1;

        case EORI: // EORI
            return 1;

        case HALT: // HALT
        {
            printDump();
            machineState.pc = -1; // End program
            return 0;
        }
        case LDUR: // LDUR
            return 1;

        case LDURB: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case LDURH: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case LDURSW: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case LSL: // LSL
        {
            uint32_t rd = reg[0];
            uint32_t rn = reg[1];
            // uint32_t rm = reg[2]; // rm unused
            uint32_t shamt = reg[3];
            machineState.registers[rd] = machineState.registers[rn] << shamt;
            return 1;
        }
        case LSR: // LSR
        {
            uint32_t rd = reg[0];
            uint32_t rn = reg[1];
            // uint32_t rm = reg[2]; // rm unused
            uint32_t shamt = reg[3];
            machineState.registers[rd] = machineState.registers[rn] >> shamt;
            return 1;
        }
        case MUL: // MUL
            return 1;

        case ORR: // ORR
            return 1;

        case ORRI: // ORRI
            return 1;

        case PRNL: // Prints a blank line
        {
            puts("");
            return 1;
        }
        case PRNT: // Prints out a register
        {
            uint32_t rd = reg[0];
            printf("X%d\t%x\t%d", rd, machineState.registers[rd], machineState.registers[rd]);
            return 1;
        }
        case SDIV: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case SMULH: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case STUR: // STUR
            return 1;

        case STURB: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case STURH: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case STURW: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        case SUB: // SUB
        {
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t rm = reg[2];
            int32_t result = machineState.registers[rn] - machineState.registers[rm];
            machineState.registers[rd] = result;
            return 1;
        }
        case SUBI: // SUBI
        {
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t im = reg[2];
            machineState.registers[rd] = machineState.registers[rn] - im;
            return 1;
        }
        case SUBIS: // SUBIS
        {
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t im = reg[2];
            int32_t result = machineState.registers[rn] - im;
            machineState.registers[rd] = result;
            setConditionRegisters(result);
            return 1;
        }
        case SUBS: // SUBS
        {
            int32_t rd = reg[0];
            int32_t rn = reg[1];
            int32_t rm = reg[2];
            int32_t result = machineState.registers[rn] - machineState.registers[rm];
            machineState.registers[rd] = result;
            setConditionRegisters(result);
            return 1;
        }
        case UDIV: // UDIV
            return 1;

        case UMULH: // NOT REQUIRED; emulator will skip this instruction
        {
            return 1;
        }
        default: // Terminate program
        {
            machineState.pc = -1;
            return 0;
        }
    }
}

void printDump()
{
    printf("----------------------------------------------------\n");
    printf("Registers\n");
    printf("----------------------------------------------------\n");
    printf("Reg#\tHex\tBinary\tBase 10\n");
    for (int i = 0; i < sizeof(machineState.registers) / sizeof(machineState.registers[0]); i++)
    {
        printf("X%d\t", i);
        printf("%x\t", machineState.registers[i]);
        printf("%s\t", int32tobin(machineState.registers[i], false));
        printf("%d\t", machineState.registers[i]);
        puts("");
    }
}

/** Sets the condition registers based on given subtraction result */
void setConditionRegisters(int32_t result)
{
    // Reset all condition registers
    for (int i = cEQ; i <= cVS; i++)
    {
        machineState.conditionRegisters[i] = 0;
    }

    if (result == 0)
    {
        machineState.conditionRegisters[cEQ] = 1;
    }
    if (result >= 0)
    {
        machineState.conditionRegisters[cGE] = 1;
    }
    if (result > 0)
    {
        machineState.conditionRegisters[cGT] = 1;
    }
    if (result > 0)
    {
        machineState.conditionRegisters[cHI] = 1;
    }
    if (result >= 0)
    {
        machineState.conditionRegisters[cHS] = 1;
    }
    if (result <= 0)
    {
        machineState.conditionRegisters[cLE] = 1;
    }
    if (result < 0)
    {
        machineState.conditionRegisters[cLO] = 1;
    }
    if (result <= 0)
    {
        machineState.conditionRegisters[cLS] = 1;
    }
    if (result < 0)
    {
        machineState.conditionRegisters[cLT] = 1;
    }
    if (result < 0)
    {
        machineState.conditionRegisters[cMI] = 1;
    }
    if (result != 0)
    {
        machineState.conditionRegisters[cNE] = 1;
    }
    if (result >= 0)
    {
        machineState.conditionRegisters[cPL] = 1;
    }
}

char* int32tobin(int32_t n, bool useSpace)
{
    char* binary = malloc(sizeof(char) * (32 + 4));
    for (int i = 31; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
        {
            strcat(binary, "1");
        }
        else
        {
            strcat(binary, "0");
        }

        if (useSpace && i % 8 == 0)
        {
            strcat(binary, " ");
        }
    }
    
    return binary;
}

/** Finds matching instruction in list and returns its index */
int findInstruction(uint32_t instruction)
{
    for (int i = 0; i < 37; i++)
    {
        // B instructions
        if (machineState.instructionOpcodes[i] == 
            ((instruction >> (32 - 6)) & 0b111111))
        {
            return i;
        }
        // CB instructions
        else if (machineState.instructionOpcodes[i] == 
            ((instruction >> (32 - 8)) & 0b11111111))
        {
            return i;
        }
        // I instructions
        else if (machineState.instructionOpcodes[i] == 
            ((instruction >> (32 - 10)) & 0b1111111111))
        {
            return i;
        }
        // R instructions
        else if (machineState.instructionOpcodes[i] == 
            ((instruction >> (32 - 11)) & 0b11111111111))
        {
            return i;
        }
        // D instructions
        else if (machineState.instructionOpcodes[i] == 
            ((instruction >> (32 - 11)) & 0b11111111111))
        {
            return i;
        }
    }

    return -1;
}

/** 
 * Parse register values from instruction binary
 * Returns an integer array with [0]:Rd, [1]:Rn, [2]:Rm/im
 */
uint32_t* parseRegisters(uint32_t instruction)
{
    // Get format of given instruction
    int instructionIndex = findInstruction(instruction);
    int32_t opcode = machineState.instructionOpcodes[instructionIndex];
    int format = machineState.instructionFormats[instructionIndex];
    int32_t* reg = malloc(4 * sizeof(int32_t)); // reg[0] = Rd, reg[1] = Rn, reg[2] = Rm/im
    reg[0] = -1;
    reg[1] = -1;
    reg[2] = -1;

    int32_t rd, rn, rm, im, adr, shamt;

    // TODO change binary to hex
    switch (format)
    {
        case fR: // 11 opcode, 5 Rm, 6 shamt, 5 Rn, 5 Rd
        {
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            shamt = (instruction >> (5 + 5)) & 0b111111;
            rm = (instruction >> (5 + 5 + 6)) & 0b11111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = rm;
            reg[3] = shamt;
            break;
        }
        case fI: // 10 opcode, 12 immediate, 5 Rn, 5 Rd
        {
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            im = (instruction >> (5 + 5)) & 0b111111111111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = im;
            break;
        }
        case fD: // 11 opcode, 9 address (offset), 2 op, 5 Rn, 5 Rt
        {
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            adr = (instruction >> (5 + 5 + 2)) & 0b111111111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = adr;
            break;
        }
        case fB: // 6 opcode, 26 address
        {
            adr = instruction & 0b11111111111111111111111111;
            // Check for negative
            if ((instruction >> 5) & 0b10000000000000000000000000)
            {
                adr = -((~instruction >> 5) & 0b01111111111111111111111111) - 1;
            }
            reg[0] = adr;
            break;
        }
        case fCB: // 8 opcode, 19 address, 5 Rt
        {
            rd = instruction & 0b11111;
            adr = (instruction >> 5) & 0b1111111111111111111;
            // Check for negative
            if ((instruction >> 5) & 0b1000000000000000000)
            {
                adr = -((~instruction >> 5) & 0b0111111111111111111) - 1;
            }
            reg[0] = rd;
            reg[1] = adr;
            break;
        }
        case fIW: // 11 opcode, 16 immediate, 5 Rd
        {
            rd = instruction & 0b11111;
            im = (instruction >> 5) & 0b1111111111111111;
            break;
        }
        default:
        {
            break;
        }
    }

    return reg;
}