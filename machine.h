#ifndef MACHINE_H
# define MACHINE_H

#include <inttypes.h>

struct MachineState
{
    // Current place in assembly
    int32_t pc;

    uint32_t instructionOpcodes[37]; // 37 = # of instructions
    int32_t instructionFormats[37];
    char* instructionStrings[37];
    char* formatStrings[6];

    int32_t registers[32];
    int32_t stack[128];
    int32_t memory[1024];

    // Available instruction formats
    const enum InstructionFormat {
        fR,
        fI,
        fD,
        fB,
        fCB,
        fIW
    } instructionFormat;
};

// struct MachineState initMachineState();

static struct MachineState machineState = {
    .instructionOpcodes = {
        0b10001011000,  // ADD
        0b1001000100,   // ADDI
        0b10001010000,  // AND
        0b1001001000,   // ANDI
        0b000101,       // B
        0b01010100,     // Bcond
        0b100101,       // BL
        0b11010110000,  // BR
        0b10110101,     // CBNZ
        0b10110100,     // CBZ
        0b11111111110,  // DUMP
        0b11001010000,  // EOR
        0b1101001000,   // EORI
        0b11111111111,  // HALT
        0b11111000010,  // LDUR
        0b00111000010,  // LDURB
        0b01111000010,  // LDURH
        0b10111000100,  // LDURSW
        0b11010011011,  // LSL
        0b11010011010,  // LSR
        0b10011011000,  // MUL
        0b10101010000,  // ORR
        0b1011001000,   // ORRI
        0b11111111100,  // PRNL
        0b1111111101,   // PRNT
        0b10011010110,  // SDIV
        0b10011011010,  // SMULH
        0b11111000000,  // STUR
        0b00111000000,  // STURB
        0b01111000000,  // STURH
        0b10111000000,  // STURW
        0b11001011000,  // SUB
        0b1101000100,   // SUBI
        0b1111000100,   // SUBIS
        0b1110101000,   // SUBS
        0b10011010110,  // UDIV
        0b10011011110   // UMULH
    },
    .instructionFormats = {
        fR, // ADD
        fI, // ADDI
        fR, // AND
        fI, // ANDI
        fB, // B
        fCB, // Bcond
        fB, // BL
        fR, // BR
        fCB, // CBNZ
        fCB, // CBZ
        fR, // DUMP
        fR, // EOR
        fI, // EORI
        fR, // HALT
        fD, // LDUR
        fD, // LDURB
        fD, // LDURH
        fD, // LDURSW
        fR, // LSL
        fR, // LSR
        fR, // MUL
        fR, // ORR
        fI, // ORRI
        fR, // PRNL
        fR, // PRNT
        fR, // SDIV
        fR, // SMULH
        fD, // STUR
        fD, // STURB
        fD, // STURH
        fD, // STURW
        fR, // SUB
        fI, // SUBI
        fI, // SUBIS
        fR, // SUBS
        fR, // UDIV
        fR, // UMULH
    },
    .instructionStrings = {
        "ADD",
        "ADDI",
        "AND",
        "ANDI",
        "B",
        "Bcond",
        "BL",
        "BR",
        "CBNZ",
        "CBZ",
        "DUMP",
        "EOR",
        "EORI",
        "HALT",
        "LDUR",
        "LDURB",
        "LDURH",
        "LDURSW",
        "LSL",
        "LSR",
        "MUL",
        "ORR",
        "ORRI",
        "PRNL",
        "PRNT",
        "SDIV",
        "SMULH",
        "STUR",
        "STURB",
        "STURH",
        "STURW",
        "SUB",
        "SUBI",
        "SUBIS",
        "SUBS",
        "UDIV",
        "UMULH"
    },
    .formatStrings = {
        "R",
        "I",
        "D",
        "B",
        "CB",
        "IW"
    },
    .registers = {
        0, // X0 Return
        0, // X1 Arg
        0, // X2 Arg
        0, // X3 Arg
        0, // X4 Arg
        0, // X5 Arg
        0, // X6 Arg
        0, // X7 Arg
        0, // X8 Indirect result
        0, // X9 Temp
        0, // X10 Temp
        0, // X11 Temp
        0, // X12 Temp
        0, // X13 Temp
        0, // X14 Temp
        0, // X15 Temp
        0, // X16 IP0
        0, // X17 IP1
        0, // X18 Temp
        0, // X19 Saved
        0, // X20 Saved
        0, // X21 Saved
        0, // X22 Saved
        0, // X23 Saved
        0, // X24 Saved
        0, // X25 Saved
        0, // X26 Saved
        0, // X27 Saved
        0, // X28 Stack Pointer (SP)
        0, // X29 Frame Pointer (FP)
        0, // X30 Link Register / return address (LR)
        0, // X31 XZR
    }
};

#endif