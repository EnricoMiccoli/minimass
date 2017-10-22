#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "registers.h"
#include "ram.h"
#include "opcodes.h"

/* Initialize registers and virtual RAM */
Register a = 0;         // A, alu
Register b = 0;         // B, alu
Register dr = 0;        // data
Register cir = 0;       // current instruction
RamAddr ar = 0;         // address
RamAddr pc = 0;         // program counter
Int ram[N_WORDS_RAM];   // RAM

int main(int argc, char *argv[]) 
{
    /* Open bytecode file */
    if (argc != 2) {
        fprintf(stderr, "Wrong arguments\n");
        exit(1);
    }
    FILE *file_ptr;
    file_ptr = fopen(argv[1], "rb");

    /* Read instructions and load onto RAM */
    Int instr;
    RamAddr i = 0;
    while (feof(file_ptr) == 0) {
        fread(&instr, sizeof(Int), 1, file_ptr);
        ram[i] = instr;
        i++;
    }
    
    /* Execution loop */
    int exec_status;
    do {
        /* Read opcode at pc */
        cir = ram[pc];
        //printf("Running instr # %d", pc);
        // For JMP to work pc must be incremented here
        pc++;

        /* Execute */
        // !! this might modify pc (via JMP and JMPZ)
        exec_status = exec_opcode(cir);
        //printf(", status %d\n", exec_status);
    } while (exec_status == 0);
    
    /* Exit */
    if (exec_status == 1) {
        return 0;
    } else {
        printf("Error: instruction #%d returned %d\n", --pc, exec_status);
        return 1;
    }
}
