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
    scanf("%d", &ram[addr]);
}

/*
 * WRITE
 * Print to screen value in ram at addr
 */
void io_write(RamAddr addr)
{
    printf("%d", ram[addr]);
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
    RamAddr operand = instruction && OPERAND_MASK;
    int opcode = instruction >> OPCODE_SHIFT;

    switch (opcode) {
        case 0000: // LOADA
            load(&a, operand);
            break;
        case 0001: // LOADB
            load(&b, operand);
            break;
        case 0010: // STOREA
            store(&a, operand);
            break;
        case 0011: // STOREB
            store(&b, operand);
            break;
        case 0110: // ADD
            add();
            break;
        case 0111: // DIF
            diff();
            break;
        case 1010: // JMP
            jump(operand);
            break;
        case 1011: // JMPZ
            if (a == 0)
                jump(operand);
            break;
        case 1100: // NOP
            break;
        case 1101: // HALT
            return 1;
            break;
        case 0100: // READ
            io_read(operand);
            break;
        case 0101: // WRITE
            io_write(operand);
            break;
        case 1000: // LDCA //TODO check bits
            load_const(&a, (int) operand);
            break;
        case 1001: // LDCB
            load_const(&b, (int) operand);
            break;
        default:
            return -1;
    }
    return 0;
}
