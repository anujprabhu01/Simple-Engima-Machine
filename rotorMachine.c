/*
 * Author: Anuj Prabhu
 * Date: 29 October 2023
 * Description: rotorMachine.c; .c file that contains all functions required for our rotor machine to function properly.
 * Usage: The functions from this file will be used to build rotos.ini file, and encyrpt or decrpyt files.
*/

#include <stdio.h>
#include "rotorMachine.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//this function builds the rotor.ini file using the given configuration file.
void buildIni(char *filename) {
	FILE* configFile;
	configFile = fopen(filename, "r"); //open given file to read.

	FILE* outFile;
	outFile = fopen("rotors.ini", "w"); //open rotors.ini file to write the encrypted integers to.

	int val = 0;

	int i;
	for(i = 0; i < 56; i++) {//loop 56 times as there are 56 integers present in the configuration file.
		fscanf(configFile, "%d", &val);//for each integer, read it.
		
		val = val ^ 42;//encrypt the integer.
		
		fprintf(outFile, "%d\n", val);//output that integer to rotors.ini file.
	}
	fclose(configFile);//close input file stream.
	fclose(outFile);//close output file stream.
}

//this fuction builds rotor 1 and rotor 2 using the encrypted integers in the rotors.ini file
void buildRotors(int rotor1[28], int rotor2[28]) {
	FILE* inputFile;
	inputFile = fopen("rotors.ini", "r");//open rotors.ini file to read.
	
	if(inputFile != NULL) {//if the input file stream exists, proceed
		int val = 0;
		
		int i;
		for(i = 0; i < 56; i++) {
			fscanf(inputFile, "%d", &val);
			
			val = val ^ 42;//decrypt encryted text in "rotors.ini" file
			
			if(i < 28) {
				rotor1[i] = val;//populate rotor1
			}
			else if(i >= 28) {//rotor2 is the next set of 28 integers
				rotor2[i - 28] = val;//populate rotor2
			}
		}       
	fclose(inputFile);
	}
	else {
		printf("Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.");//input file stream does not exist.
	}
}

//this function rotates each value of a rotor right by 1 position
void rotateRotorRight(int rotor[28]) {
	int i = 0, j, temp;
	for(j = i + 1; j < 28; j++) {//from left to right, swap rotor values with first position of array. Each swap places that rotor value in correct position.
		temp = rotor[j];
		rotor[j] = rotor[i];
		rotor[i] = temp;
	}	
}

//this function rotates each value of a rotor left by 1 position
void rotateRotorLeft(int rotor[28]) {
	int i = 27, j, temp;
	for(j = i - 1; j >= 0; j--) {//from right to left, swap rotor values with last position of array. Each swap places that rotor value in correct position.
		temp = rotor[j];
		rotor[j] = rotor[i];
		rotor[i] = temp;
	}
}

//this function sets rotor1 to its initial position, given by "rotations".
void setRotor1(int rotor[28], int rotations) {
	int i = 0;
	while(i < rotations) {
		rotateRotorRight(rotor);
		i++;
	}
}

//this function rotates rotor2 to its initial position, given by "rotations".
void setRotor2(int rotor[28], int rotations) {
	int i = 0;
	while(i < rotations) {
		rotateRotorLeft(rotor);
		i++;
	}
}

//this function converts all lowercase characters to uppercase and then coverts those uppercases to indexes using ASCII math.
int charToIndex(char convert) {
	int pos = 0;

	convert = toupper(convert);
	
	if(convert == ' ') {
		return 26;
	}
	else if(convert == '.') {
		return 27;
	}
	else {
		pos = (int)convert - 65;
		return pos;
	}
}

//this function  converts all indexed to uppercase characters using ASCII math.
char indexToChar(int convert) {
	char ch;

	if (convert == 26) {
		return ' ';
	}
	else if(convert == 27) {
		return '.';
	}
	else {
		ch = (char)convert + 65;
		return ch;
	}
}

//this function encrypts contents of infile and writes those encrypted contents to outfile. encryption depends on rotor1 and rotor2 configuration.
void encryptFile(FILE* infile,FILE* outfile,int rotor1[28],int rotor2[28]) {
	char buffer[256];//limit max 256 characters in one line
	while(fgets(buffer, 256, infile)) {//get each line from infile
		int i = 0, j;
		char ch;
		int scramb = 0;
		while(buffer[i] != '\0') {//as long as the termination character is not encountered, proceed to encryption
			if(buffer[i] == '\n') {//if newline is encountered, print newline to outfile
				fprintf(outfile, "\n");
				i++;//proceed to next character
				continue;
			}
			//printf("%c", buffer[i]);
			scramb = rotor1[charToIndex(buffer[i])];//get index of current character in buffer and store encrypted value at that index of rotor1 in scramb.
			//printf("Char: %c | Num: %d\n",buffer[i], scramb);
			
			for(j = 0; j < 28; j++) {//search for scramb in rotor2.
				if(rotor2[j] == scramb) {//if found, exit the loop
					break;
				}
			}
			ch = indexToChar(j);//use that current index of scramb in rotor2 and convert that to its corresponding character. 
			fprintf(outfile, "%c", ch);//print that encrypted character to outfile
			
			rotateRotorRight(rotor1);//rotate rotor1 right by 1 posiiton after each character is encrypted.
			rotateRotorLeft(rotor2);//rotate rotor2 left by 1 position after each character is encrypted.
		i++;
		}
		//fprintf(outfile, "\n");
	}
	fclose(infile);//close input file stream.
	fclose(outfile);//close output file stream.
}

//this function decrypts contents of infile and writes those decrypted contents to outfile. decryption depends on rotor1 and rotor2 configuration.
void decryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {
	char buffer[256];//limit max 256 characters in one line
	while(fgets(buffer, 256, infile)) {//get each line from infile
		int i = 0, j;
		char ch;
		int scramb = 0;
		while(buffer[i] != '\0') {//as long as the termination character is not encountered, proceed to decryption
			if (buffer[i] == '\n') {//if newline is encountered, print newline to outfile
				fprintf(outfile, "\n");
				i++;//proceed to next character
				continue;
			}
			scramb = rotor2[charToIndex(buffer[i])];//get index of current character in buffer and store decrypted value at that index of rotor2 in scramb.
			
			for(j = 0; j < 28; j++) {//search for scramb in rotor1.
				if(rotor1[j] == scramb) {//if found exit the loop
					break;
				}
			}
			ch = indexToChar(j);//use that current index of scramb in rotor1 and convert that to its corresponding character.
			fprintf(outfile, "%c", ch);//print that decrypted character to outfile

			rotateRotorRight(rotor1);//rotate rotor1 right by 1 position after each character is decrypted.
			rotateRotorLeft(rotor2);//rotate rotor2 left by one position after each character is decrypted.
		i++;
		}
		//fprintf(outfile, "\n");
	}
	fclose(infile);//close input file stream.
	fclose(outfile);//close output file stream.
}
