# minimass
A miniature assembler running on a mini-cpu.

The mini-cpu architecture was developed as a teaching tool by professor Daniele Braga at Politecnico di Milano, deriving from the abstract machine presented in the book [*Informatica: arte e mestiere*](http://www.catalogo.mcgraw-hill.it/catLibro.asp?item_id=2981).

This project implements the relative assembly-like language and an emulator to run it.

## Running your first program
```
$ make all
$ ./assembler examples/sum.masm
$ ./runner examples/sum
```

## Available instructions, registers and memory
All instructions are called as follows:
```
OPCODE <operand>
```
except `ADD, DIF, NOP, HALT` that require no operand.

```
OPCODES         <op> type
0000  0  LOADA    addr.    copy in A the value from RAM cell <op>
0001  1  LOADB    addr.    copy in B the value from RAM cell <op>
0010  2  STOREA   addr.    store in RAM cell <op> the value from A
0011  3  STOREB   addr.    store in RAM cell <op> the value from B
0100  4  READ     addr.    read from console, store in RAM cell <op>
0101  5  WRITE    addr.    write to console from RAM cell <op>
0110  6  ADD      -        load A + B in A
0111  7  DIF      -        load A - B in A
1000 -8  LDCA     value    load <op> in A
1001 -7  LDCB     value    load <op> in B
1010 -6  JMP      addr.    run instruction at RAM cell <op> next
1011 -5  JMPZ     addr.    do the same as jump, if A == 0
1100 -4  NOP      -        do nothing
1101 -3  HALT     -        stop execution
```
