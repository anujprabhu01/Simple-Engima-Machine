#Author: Anuj Prabhu
#Date: 1 November 2023
#Description: Makefile; file compiles all code together into a single executable.
#Usage: -make

OBJS = prabhu_anuj_assn3.o rotorMachine.o
EXE = exe
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c -g
LFLAG = -Wall -g

exe : prabhu_anuj_assn3.o rotorMachine.o
	gcc -Wall -g prabhu_anuj_assn3.o rotorMachine.o -o exe

prabhu_anuj_assn3.o: rotorMachine.h
	gcc -Wall -c -g prabhu_anuj_assn3.c

rotorMachine.o: rotorMachine.h
	gcc -Wall -c -g rotorMachine.c

clean:
	rm *.o exe -v
