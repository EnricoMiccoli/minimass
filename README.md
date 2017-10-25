# minimass
A miniature assembler running on a mini-cpu.

## Running your first program
```
$ make all
$ ./assembler examples/sum.masm
$ ./runner examples/sum
```

## Available instructions

```
OPCODES
0000  0  LOADA
0001  1  LOADB
0010  2  STOREA
0011  3  STOREB
0100  4  READ
0101  5  WRITE
0110  6  ADD
0111  7  DIF
1000 -8  LDCA
1001 -7  LDCB
1010 -6  JMP
1011 -5  JMPZ
1100 -4  NOP
1101 -3  HALT
```
