//TODO ifndef

#define OPERAND_MASK (1 << 12) - 1
#define OPCODE_SHIFT 12

/*
 * LOADA, LOADB
 * Read value at addressed ram and write 
 * it in register A or B
 */
void load(Register *reg_ptr, RamAddr addr)
{
    *reg_ptr = ram[addr];
}

/*
 * STOREA, STOREB
 */
void store(Register *reg_ptr, RamAddr addr)
{
    ram[addr] = *reg_ptr;
}

//TODO signal overflow
/*
 * ADD
 * Store A + B in A
 */
void add()
{
    a += b;
}

/*
 * DIF
 * Store A - B in A
 */
void diff()
{
    a -= b;
}

/*
 * JMP
 * Set next instruction to addr
 */
void jump(RamAddr addr)
{
    pc = addr;
}
    
/*
 * READ
 * Read Int from keyboard and store in ram at addr
 */
void io_read(RamAddr addr)
{
    int temp;
    printf("> ");
    scanf("%d", &temp);
    ram[addr] = (Int) temp;
}

/*
 * WRITE
 * Print to screen value in ram at addr
 */
void io_write(RamAddr addr)
{
    printf("%d\n", ram[addr]);
}

/*
 * LDCA, LDCB
 * Load constant in register A or B
 */
void load_const(Register *reg_ptr, int value)
{
    *reg_ptr = value;
}

/*
 * Parse the instruction, get opcode and operand
 * Then execute the instruction and return a code:
 *      0: success
 *      1: instruction is HALT
 *     -1: unknown instruction, abort
 */
int exec_opcode(int instruction)
{
    // TODO make proper length: 12b and 4b
    RamAddr operand = instruction & (OPERAND_MASK);
    int opcode = instruction >> OPCODE_SHIFT;
    //printf("~%d\n", opcode);

    switch (opcode) {
        case 0: // LOADA
            load(&a, operand);
            break;
        case 1: // LOADB
            load(&b, operand);
            break;
        case 2: // STOREA
            store(&a, operand);
            break;
        case 3: // STOREB
            store(&b, operand);
            break;
        case 4: // READ
            io_read(operand);
            break;
        case 5: // WRITE
            io_write(operand);
            break;
        case 6: // ADD
            add();
            break;
        case 7: // DIF
            diff();
            break;
        case 8: // LDCA //TODO check bits
            load_const(&a, (int) operand);
            break;
        case 9: // LDCB
            load_const(&b, (int) operand);
            break;
        case 10: // JMP
            jump(operand);
            break;
        case 11: // JMPZ
            if (a == 0)
                jump(operand);
            break;
        case 12: // NOP
            break;
        case -3: // HALT
            return 1;
            break;
        default:
            return -1;
    }
    return 0;
}
