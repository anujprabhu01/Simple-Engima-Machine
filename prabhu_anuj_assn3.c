/*
 * Author: Anuj Prabhu
 * Date: 30 October 2023
 * Description: prabhu_anuj_assn3.c; Main file; driver file that performs program's full functionality.
 * Usage: 
 * ./exe -i <file>
 * ./exe -e <file1> <file2> -r <r1> <r2>
 * ./exe -d <file1> <file2> -r <r1> <r2>
 * ./exe -e <file1> <file2> -r <r1> <r2> -i <file>
 * ./exe -d <file1> <file2> -r <r1> <r2> -i <file>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rotorMachine.h"

int main (int argc, char **argv) {
	printf("%d\n", argc);//FIXME
	int rotor1[28];
	int rotor2[28];

	if(argc != 3 && argc != 7 && argc != 9) {//checking for invalid number of arguments
		printf("entering argc != 3 ...");//FIXME
		printf("usage");
		printf("\n./exe -i <file>");
		printf("\n./exe -e <file1> <file2> -r <r1> <r2>");
		printf("\n./exe -d <file1> <file2> -r <r1> <r2>");
		printf("\n./exe -e <file1> <file2> -r <r1> <r2> -i <file>");
		printf("\n./exe -d <file1> <file2> -r <r1> <r2> -i <file>");
	}
	else {
		if(argc == 3 && strcmp(argv[1], "-i") == 0) {//checking if all arguments are valid for building rotors.ini file
			buildIni(argv[2]);
		}
		else if(argc == 7 && 
			(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) && 
			strcmp(argv[4], "-r") == 0) {//checking if all arguments are valid for encrypting or decrypting a file
			
			if(strcmp(argv[1], "-e") == 0) {//for encyrpting
				
				FILE* infile = fopen(argv[2], "r");//opening input filestream to read and setting that to a file pointer
				FILE* outfile = fopen(argv[3], "w");//opening output filestream to write to
				
				buildRotors(rotor1, rotor2);//building rotors
				
				setRotor1(rotor1, atoi(argv[5]));//setting rotor1 to initial posiiton
				setRotor2(rotor2, atoi(argv[6]));//setting rotor2 to initial position

				encryptFile(infile, outfile, rotor1, rotor2);//encrypting given file with rotor settings
			}
			else if(strcmp(argv[1], "-d") == 0) {//for decrypting
				
				FILE* infile = fopen(argv[2], "r");
				FILE* outfile = fopen(argv[3], "w");

				buildRotors(rotor1, rotor2);
				
				setRotor1(rotor1, atoi(argv[5]));
				setRotor2(rotor2, atoi(argv[6]));

				decryptFile(infile, outfile, rotor1, rotor2);
			}
			else {//if invalid arguments, then print error message
				printf("usage");
				printf("\n./exe -i <file>");
				printf("\n./exe -e <file1> <file2> -r <r1> <r2>");
				printf("\n./exe -d <file1> <file2> -r <r1> <r2>");
				printf("\n./exe -e <file1> <file2> -r <r1> <r2> -i <file>");
				printf("\n./exe -d <file1> <file2> -r <r1> <r2> -i <file>");
			}
		}
		else if(argc == 9 && 
			(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) && 
			strcmp(argv[4], "-r") == 0 && 
			strcmp(argv[7], "-i") == 0) {//checking if all arguments are valid for building rotors.ini file with given configuration and using that to encrypt or decrypt a file
			
			FILE* infile = fopen(argv[2], "r");
			FILE* outfile = fopen(argv[3], "w");
			
			buildIni(argv[8]);
			
			buildRotors(rotor1, rotor2);
			
			setRotor1(rotor1, atoi(argv[5]));
			setRotor2(rotor2, atoi(argv[6]));
			if (strcmp(argv[1], "-e") == 0) {//if user wants to encrypt
				encryptFile(infile, outfile, rotor1, rotor2);
			}
			else if(strcmp(argv[1], "-d") == 0) {//if user wants to decrypt
				decryptFile(infile, outfile, rotor1, rotor2);
			}
			else {//if invalid arguments, then print error message
				printf("usage");
				printf("\n./exe -i <file>");
				printf("\n./exe -e <file1> <file2> -r <r1> <r2>");
				printf("\n./exe -d <file1> <file2> -r <r1> <r2>");
				printf("\n./exe -e <file1> <file2> -r <r1> <r2> -i <file>");
				printf("\n./exe -d <file1> <file2> -r <r1> <r2> -i <file>");
			}
		}
		else {//if invalid arguments, then print error message
			printf("usage");
			printf("\n./exe -i <file>");
			printf("\n./exe -e <file1> <file2> -r <r1> <r2>");
			printf("\n./exe -d <file1> <file2> -r <r1> <r2>");
			printf("\n./exe -e <file1> <file2> -r <r1> <r2> -i <file>");
			printf("\n./exe -d <file1> <file2> -r <r1> <r2> -i <file>");
		}
	}

	return 0;
}
