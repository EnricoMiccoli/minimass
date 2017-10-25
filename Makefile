.PHONY: all
all:
	gcc runner.c -o runner -Wall
	gcc assembler.c -o assembler -Wall

runner: opcodes.h ram.h registers.h runner.c
	gcc runner.c -o runner -Wall

assembler: assembler.c
	gcc assembler.c -o assembler -Wall
