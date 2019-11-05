# Binary Emulator

## File Descriptions
- `legv8asm` is an LEGv8 (sub-set of ARMv8) instruction set emulator that is used to produce binary output of an assembled program. Created by my instructor, Jeremy Sheaffer.
- `test.legv8asm` is a LEGv8 assembly program in plain text
- `test.legv8asm.machine` is the binary version of `test.legv8asm` after being assembled with `./legv8asm test.legv8asm -a`

## How To Use
1. Clone repository to local machine; `git clone https://github.com/ASTRELION/BinaryEmulator`
2. Cd into repo; `cd BinaryEmulator`
3. Compile; `make`
4. Create/modify `test.legv8asm` to include assembly instructions
5. Run `./legv8asm test.legv8asm -a` to assemble program into binary. A file named `test.legv8asm.machine` will be generated as a binary file
6. Run `./main` to run `test.legv8asm.machine` and observe output
