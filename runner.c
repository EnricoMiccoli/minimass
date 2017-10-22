#include <stdio.h>
#include <stdint.h>

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

int main() 
{
    /* Read instructions and load onto RAM */
    
    /* Execution loop */
    int exec_status;
    do {
        /* Read opcode at pc */
        cir = ram[pc];
        // For JMP to work pc must be incremented here
        pc++;

        /* Execute */
        // !! this has side effects
        // !! this might modify pc (via JMP and JMPZ)
        exec_status = exec_opcode(cir);
    } while (exec_status == 0);
    
    /* Exit */
    if (exec_status == 1) {
        //halt();
        return 0;
    } else {
        //get_broken();
        return 1;
    }
}
