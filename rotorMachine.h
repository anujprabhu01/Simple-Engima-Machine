/*
 * Author: Anuj Prabhu
 * Date: 29 October 2023
 * Description: rotorMachine.h; .h file that includes prototypes for the rotorfile.c function definitions.
 * Usage: #include "rotorMachine.h"
 */

#ifndef ROTORMACHINE_H//define macro to protect the contents of .h file from multiple declaration
#define ROTORMACHINE_H

//forward declarations for functions in rotorMachine.c file
void buildIni(char *);
void buildRotors(int[28], int[28]);
void rotateRotorRight(int[28]);
void rotateRotorLeft(int[28]);
void setRotor1(int[28], int);
void setRotor2(int[28], int);
int charToIndex(char);
char indexToChar(int);
void encryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);
void decryptFile(FILE*, FILE*, int rotor1[28], int rotor2[28]);

#endif
