#ifndef MAIN_H
# define MAIN_H

/** 32 main registers */
int registers[32] = {
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
};

/** Main memory has 512 integers */
int memory[512];

#endif