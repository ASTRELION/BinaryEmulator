#ifndef MACHINE_H
# define MACHINE_H

#include <inttypes.h>

struct MachineState
{
    // Current place in assembly
    int32_t pc;

    // Array of instruction opcodes in 0b<opcode> format
    uint32_t instructionOpcodes[37]; // 37 = # of instructions
    // Array of instruction formats for each corresponding instruction
    int32_t instructionFormats[37];
    // Array of instruction strings
    char* instructionStrings[37];
    // Array of format type strings
    char* formatStrings[6];

    // Find condition register by >> number of bits
    uint8_t conditionRegisters[14];
    // Main 32 registers
    int32_t registers[32];
    // Main stack; array of 8-bit integers
    uint8_t *stack;
    // Main memory; array of 8-bit integers
    uint8_t *memory;

    // Instruction Formats
    const enum InstructionFormat {
        fR,
        fI,
        fD,
        fB,
        fCB,
        fIW
    } instructionFormat;

    // Instruction Names
    const enum InstructionNames {
        ADD,
        ADDI,
        AND,
        ANDI,
        B,
        Bcond,
        BL,
        BR,
        CBNZ,
        CBZ,
        DUMP,
        EOR,
        EORI,
        HALT,
        LDUR,
        LDURB,
        LDURH,
        LDURSW,
        LSL,
        LSR,
        MUL,
        ORR,
        ORRI,
        PRNL,
        PRNT,
        SDIV,
        SMULH,
        STUR,
        STURB,
        STURH,
        STURW,
        SUB,
        SUBI,
        SUBIS,
        SUBS,
        UDIV,
        UMULH
    } instructionNames;

    const enum Conditions {
        cEG,
        cNE,
        cHS,
        cLO,
        cMI,
        cPL,
        cVS,
        cVC,
        cHI,
        cLS,
        cGE,
        cLT,
        cGT,
        cLE
    } conditions;
};

// Current machine state (registers, memory, etc.)
extern struct MachineState machineState;

/** Initializes machineState to base values */
void initMachineState();

#endif