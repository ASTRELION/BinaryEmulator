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
    char* binary = malloc(37); // 4 for num 1 for \0
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
        instr = be32toh(instr);
        instructions[i] = instr;
        i++;
    }
    
    printf("%s", opcodes[0]);
    printf("File Size: %u bytes\n", fileLength);
    printf("Instruction Count: %u\n", fileLength / 4);
    printf("\nInstructions: \n");

    for (int i = 0; i < sizeof(instructions) / 4; i++)
    {
        printf("%x ", instructions[i]);
        printf("%s\n", int32tobin(instructions[i], true));
    }

    FILE* test = fopen("test.machine", "wb");
    uint32_t j = 3;
    fwrite(&j, sizeof(j), 1, test);
 
    return 0;
}