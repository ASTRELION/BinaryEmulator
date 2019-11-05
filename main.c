#include "main.h"
#include "machine.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <endian.h>
#include <string.h>
#include <stdbool.h>

/**
 * Convert given uint32_t to a binary string
 */
/*
char* int32tobin(uint32_t n, bool useSpace)
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
*/

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

/** Parse register values from instruction binary */
int * parseRegisters(uint32_t instruction)
{
    // Get format of given instruction
    int instructionIndex = findInstruction(instruction);
    int32_t opcode = machineState.instructionOpcodes[instructionIndex];
    int format = machineState.instructionFormats[instructionIndex];
    int* reg = malloc(3 * sizeof(int)); // reg[0] = Rd, reg[1] = Rn, reg[2] = Rm/im
    reg[0] = -1;
    reg[1] = -1;
    reg[2] = -1;

    int32_t rd, rn, rm, im, adr;

    // TODO change binary to hex
    switch (format)
    {
        case fR: // 11 opcode, 5 Rm, 6 shamt, 5 Rn, 5 Rd
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            rm = (instruction >> (5 + 5 + 6)) & 0b11111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = rm;
            break;
        
        case fI: // 10 opcode, 12 immediate, 5 Rn, 5 Rd
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            im = (instruction >> (5 + 5)) & 0b111111111111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = im;
            break;

        case fD: // 11 opcode, 9 address (offset), 2 op, 5 Rn, 5 Rt
            rd = instruction & 0b11111;
            rn = (instruction >> 5) & 0b11111;
            adr = (instruction >> (5 + 5 + 2)) & 0b111111111;
            reg[0] = rd;
            reg[1] = rn;
            reg[2] = adr;
            break;

        case fB: // 6 opcode, 26 address
            adr = instruction & 0b11111111111111111111111111;
            reg[0] = adr;
            break;

        case fCB: // 8 opcode, 19 address, 5 Rt
            rd = instruction & 0b11111;
            adr = (instruction >> 5) & 0b1111111111111111111;
            reg[0] = rd;
            reg[1] = adr;
            break;

        case fIW: // 11 opcode, 16 immediate, 5 Rd
            rd = instruction & 0b11111;
            im = (instruction >> 5) & 0b1111111111111111;
            break;

        default:
            break;
    }

    return reg;
}

int main()
{   
    FILE *file = fopen("test.legv8asm.machine", "r"); // Open file
    fseek(file, 0, SEEK_END); // Go to end of file to get length
    int fileLength = ftell(file); // In bytes, so divide by 4 for number of 32 bit instructions
    rewind(file); // Return to file start

    uint32_t instructions[fileLength / 4];
    
    // Read file
    int c, i = 0;
    uint32_t instr;
    while (fread(&instr, sizeof(uint32_t), 1, file))
    {   
        instr = be32toh(instr); // Convert instruction to host endian-ness
        instructions[i] = instr;
        i++;
    }
    
    // Print file stats
    printf("File Size: %u bytes\n", fileLength);
    printf("Instruction Count: %u\n", fileLength / 4);
    printf("\nInstructions: \n");

    // Print Instructions
    for (int i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++)
    {
        int instrIndex = findInstruction(instructions[i]);
        printf("%d|", instrIndex);
        printf("%s\t", machineState.instructionStrings[instrIndex]);
        printf("%d|", machineState.instructionFormats[instrIndex]);
        printf("%s\t", machineState.formatStrings[machineState.instructionFormats[instrIndex]]); 

        int* registers = parseRegisters(instructions[i]);
        printf(" %d ", registers[0]);
        printf(" %d ", registers[1]);
        printf(" %d ", registers[2]);
        puts("");
    }

    return 0;
}