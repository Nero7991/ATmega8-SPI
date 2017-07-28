/*
 * Essential.h
 *
 * Created: 7/23/2017 5:09:13 PM
 *  Author: orencollaco
 */ 


#ifndef ESSENTIAL_H_
#define ESSENTIAL_H_
#include "ATmega8A.h"
void Notify(const char* str);
void printHexNumber(uint64_t data,uint8_t length);
char* hexArrayToString(uint8_t *data, uint8_t length);
uint8_t* numToArray(uint64_t data);
void printStringNL(char *p);
void printStringCRNL(const char *p);
void printString(const char *p);
void printChar(unsigned char data);
void printStringNL1(char *p);
void printStringCRNL1(const char *p);
void printString1(const char *p);
void printChar1(unsigned char data);
unsigned char hexToASCII(unsigned char data);
unsigned char charToHex(char *p);
char* hexToString(unsigned char data);
void copyArray(uint8_t *a1, uint8_t *a2, uint8_t length);

#endif /* ESSENTIAL_H_ */