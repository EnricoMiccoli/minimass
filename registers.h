//TODO ifndef

/*
 * Initialize registers as global vars
 */

typedef int16_t Register;
typedef int16_t Int;
typedef int RamAddr; // RAM Address

// A, B
extern Register a, b;

// Current instruction register, data register
extern Register cir, dr;

// Address register, program counter
extern RamAddr ar, pc; // Max 12 bit

/*
 * Are ar and dr rendered obsolete by the use of 
 * LOADA, LOADB? These registers were never used in the
 * implementation
 */
