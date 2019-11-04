#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H

/** Available instructions */
const enum instructionSet {
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
} instructionSet;

/** Instruction formats */
const enum instructionFormats {
    fR,
    fI,
    fD,
    fB,
    fCB,
    fIW
} instructionFormats;

/** Instruction format for each instruction */
const int instructionFormat[] = {
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
};

/** Opcode for each instruction */
const char* opcodes[] = {
    "10001011000",  // ADD
    "1001000100",   // ADDI
    "10001010000",  // AND
    "1001001000",   // ANDI
    "000101",       // B
    "01010100",     // Bcond
    "100101",       // BL
    "11010110000",  // BR
    "10110101",     // CBNZ
    "10110100",     // CBZ
    "11111111110",  // DUMP
    "11001010000",  // EOR
    "1101001000",   // EORI
    "11111111111",  // HALT
    "11111000010",  // LDUR
    "00111000010",  // LDURB
    "01111000010",  // LDURH
    "10111000100",  // LDURSW
    "11010011011",  // LSL
    "11010011010",  // LSR
    "10011011000",  // MUL
    "10101010000",  // ORR
    "1011001000",   // ORRI
    "11111111100",  // PRNL
    "1111111101",   // PRNT
    "10011010110",  // SDIV
    "10011011010",  // SMULH
    "11111000000",  // STUR
    "00111000000",  // STURB
    "01111000000",  // STURH
    "10111000000",  // STURW
    "11001011000",  // SUB
    "1101000100",   // SUBI
    "1111000100",   // SUBIS
    "1110101000",   // SUBS
    "10011010110",  // UDIV
    "10011011110"   // UMULH
};

const char* instructionStrings[] = {
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
};

#endif