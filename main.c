#include "main.h"
#include "instructions.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <endian.h>
#include <string.h>
#include <stdbool.h>

/**
 * Convert given uint32_t to a binary string
 */
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

/**
 * Returns instruction number based on given opcode
 */
int findInstruction(char* binary)
{
    char* result = NULL;
    int index = -1;
    for (int o = 0; o < sizeof(opcodes) / sizeof(opcodes[0]); o++)
    {
        char* opcode = malloc(sizeof(opcodes[o]));
        strcpy(opcode, opcodes[o]);
        bool validOpcode = true;

        for (int b = 0; b < strlen(opcode); b++)
        {
            if(opcode[b] != binary[b])
            {
                validOpcode = false;
                break;
            }
        }

        if (validOpcode)
        {
            if (result == NULL || strlen(opcode) < strlen(result))
            {
                index = o;
                result = opcode;
            }
        }
    }

    return index;
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
        char* binary = int32tobin(instructions[i], false);
        printf("%s\t", instructionStrings[findInstruction(binary)]);
        printf("%x\t", instructions[i]);
        printf("%s\n", int32tobin(instructions[i], true));
    }
 
    return 0;
}