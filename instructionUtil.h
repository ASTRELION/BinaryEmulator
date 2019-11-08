#ifndef INSTRUCTIONUTIL_H
# define INSTRUCTIONUTIL_H

#include "machine.h"

#include <stdbool.h>
#include <stdint.h>

struct MachineState machineState;

int32_t runInstruction(uint32_t instruction);
char* int32tobin(int32_t n, bool useSpace);
int findInstruction(uint32_t instruction);
uint32_t* parseRegisters(uint32_t instruction);
void printDump();

#endif