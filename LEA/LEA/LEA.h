#ifndef _LEA_H_
#define _LEA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE; //1byte
typedef unsigned long int WORD; //4byte 

int ROL(int i, WORD value);
int ROR(int i, WORD value);
void KeySchedule_128(BYTE *K, WORD *RK);
void KeySchedule_192(BYTE *K, WORD *RK);
void KeySchedule_256(BYTE *K, WORD *RK);
void Encrypt(int Nr, WORD *RK, BYTE *P, BYTE *C);
void Decrypt(int Nr, WORD *RK, BYTE *D, BYTE *C);

#else
#endif