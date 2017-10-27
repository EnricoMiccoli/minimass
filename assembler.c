#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

#define EXT_INFILE ".masm"
#define LEN_MAX_OPERAND 6
#define LEN_MAX_OPCODE 8
#define OPCODE_SHIFT 12
#define N_OPCODES 14

/*
 * Remove .masm extension from path
 */
void clean_name(char *path)
{
   int len = strlen(path);
   int ext_len = strlen(EXT_INFILE);
   if (len <= ext_len)
       exit(1);
   int i;
   for (i = 0; i < ext_len; i++) {
       if (EXT_INFILE[ext_len - i] != path[len - i])
           exit(1);
   }
   if (ext_len != i)
       exit(1);
   path[len - i] = '\0';
}

/*
 * Build instruction from binary opcode and operand
 */
int16_t build_instr(int opcode, int operand)
{
    unsigned int instr = 0;
    //TODO ensure proper size of ops
    instr = instr | (opcode << OPCODE_SHIFT);
    instr = instr | operand;
    return (int16_t) instr;
}

/*
 * Encode opcode string into int
 */
int encode_opcode(char opcode[])
{
    //TODO hashtable or binary search

    int i;
    char names[N_OPCODES][LEN_MAX_OPCODE] = {
        "LOADA",
        "LOADB",
        "STOREA",
        "STOREB",
        "READ",
        "WRITE",
        "ADD",
        "DIF",
        "LDCA",
        "LDCB",
        "JMP",
        "JMPZ",
        "NOP",
        "HALT"
    };
    for (i = 0; i < N_OPCODES; i++) {
        if (strcmp(opcode, names[i]) == 0)
            return i;
    }
    exit(1); // Opcode not found!
    return -1;
}
    
/*
 * Write instruction
 * Convert ops to binary, build instruction, write to outfile
 */
void write_instr(FILE *file_ptr, char opcode[], char operand[])
{
    int int_opcode = encode_opcode(opcode);
    int int_operand = atoi(operand);
    int16_t instr = build_instr(int_opcode, int_operand);

    fwrite(&instr, sizeof(instr), 1, file_ptr);
}

int main(int argc, char *argv[])
{
    /* Open files */
    if (argc != 2) {
        fprintf(stderr, "Wrong arguments\n");
        exit(1);
    }

    FILE *infile_ptr, *outfile_ptr;
    infile_ptr = fopen(argv[1], "r");
    clean_name(argv[1]);
    outfile_ptr = fopen(argv[1], "wb");

    if (infile_ptr == NULL) {
        fprintf(stderr, "Can't read input file\n");
        exit(1);
    }
    if (outfile_ptr == NULL) {
        fprintf(stderr, "Can't write output file\n");
        exit(1);
    }

    /* Parse input file and assemble outfile */
    int c = (int) 'a';  // cast as int s.t. it can store EOF
    char operand[LEN_MAX_OPERAND];
    char opcode[LEN_MAX_OPCODE];
    int i = 0;
    int is_opcode = 1;
    int is_comment = 0;

    while(c != EOF) {
        //TODO check against empty file,
        // allow multiple whitespace chars before operand
        // Eg 
        // case ' ':
        //     waiting_for_operand = 1;
        // ...
        // default:
        //     if (waiting_for_operand) {...}
        c = fgetc(infile_ptr);
        switch (c) {
            case ';':
                is_comment = 1;
                break;
            case ' ':
            case '\t':
                if (is_comment == 0 && is_opcode == 1) {
                    opcode[i] = '\0';
                    i=0;
                    is_opcode = 0;
                }
                break;
            case '\n':
            case '\r':
                if (is_opcode) {
                    opcode[i] = '\0';
                    strcpy(operand, "0");
                } else {
                    operand[i] = '\0';
                }
                write_instr(outfile_ptr, opcode, operand);
                i = 0;
                is_opcode = 1;
                is_comment = 0;
                break;
            default:
                if (is_comment == 0) {
                    if (is_opcode == 1)
                        opcode[i] = c;
                    else
                        operand[i] = c;
                    i++;
                }
        }
    }
    
    fclose(infile_ptr);
    fclose(outfile_ptr);
    return 0;
}
