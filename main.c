#include "main.h"
#include "machine.h"
#include "instructionUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <endian.h>
#include <string.h>
#include <stdbool.h>

void execute(int32_t instructions[], uint32_t size)
{
    while (machineState.pc >= 0 && machineState.pc < size)
    {
        int32_t dPC = runInstruction(instructions[machineState.pc]);
        machineState.pc += dPC;
    }
}

int main()
{   
    initMachineState();

    FILE *file = fopen("test.legv8asm.machine", "r"); // Open file
    fseek(file, 0, SEEK_END); // Go to end of file to get length
    int fileLength = ftell(file); // In bytes, so divide by 4 for number of 32 bit instructions
    rewind(file); // Return to file start

    uint32_t instructions[fileLength / 4];

    printf("%s", machineState.formatStrings[0]);
    
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

    execute(instructions, fileLength / 4);

    return 0;
}