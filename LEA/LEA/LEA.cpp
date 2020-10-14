#include "lea.h"

WORD delta[8] = {
	0xc3efe9db,
	0x44626b02,
	0x79e27c8a,
	0x78df30ec,
	0x715ea49e,
	0xc785da0a,
	0xe04ef22a,
	0xe5c40957
};

//32비트 비트열 x의 i비트 좌측 순환이동
int ROL(int i, WORD value)
{
	return (value << i) | (value >> (32 - i));
}

//32비트 비트열 x의 i비트 우측 순환이동
int ROR(int i, WORD value)
{
	return (value >> i) | (value << (32 - i));
}

void KeySchedule_128(BYTE *K, WORD *RK)
{
	WORD T[4];

	memcpy(T, K, 16); //8*16 = 128

	for (int i = 0; i < 24; i++)
	{
		T[0] = ROL(1, T[0] + ROL(i, delta[i % 4]));
		T[1] = ROL(3, T[1] + ROL(i + 1, delta[i % 4]));
		T[2] = ROL(6, T[2] + ROL(i + 2, delta[i % 4]));
		T[3] = ROL(11, T[3] + ROL(i + 3, delta[i % 4]));
		RK[i * 6 + 0] = T[0];
		RK[i * 6 + 1] = T[1];
		RK[i * 6 + 2] = T[2];
		RK[i * 6 + 3] = T[1];
		RK[i * 6 + 4] = T[3];
		RK[i * 6 + 5] = T[1];
	}
}

void KeySchedule_192(BYTE *K, WORD *RK)
{
	WORD T[6];

	memcpy(T, K, 24); //8*24 = 192

	for (int i = 0; i < 28; i++)
	{
		T[0] = ROL(1, T[0] + ROL(i, delta[i % 6]));
		T[1] = ROL(3, T[1] + ROL(i + 1, delta[i % 6]));
		T[2] = ROL(6, T[2] + ROL(i + 2, delta[i % 6]));
		T[3] = ROL(11, T[3] + ROL(i + 3, delta[i % 6]));
		T[4] = ROL(13, T[4] + ROL(i + 4, delta[i % 6]));
		T[5] = ROL(17, T[5] + ROL(i + 5, delta[i % 6]));
		RK[i * 6 + 0] = T[0];
		RK[i * 6 + 1] = T[1];
		RK[i * 6 + 2] = T[2];
		RK[i * 6 + 3] = T[3];
		RK[i * 6 + 4] = T[4];
		RK[i * 6 + 5] = T[5];
	}
}

void KeySchedule_256(BYTE *K, WORD *RK)
{
	WORD T[8];

	memcpy(T, K, 32); //8*32 = 256

	for (int i = 0; i < 32; i++)
	{
		T[(6 * i + 0) % 8] = ROL(1, T[(6 * i + 0) % 8] + ROL(i, delta[i % 8]));
		T[(6 * i + 1) % 8] = ROL(3, T[(6 * i + 1) % 8] + ROL(i + 1, delta[i % 8]));
		T[(6 * i + 2) % 8] = ROL(6, T[(6 * i + 2) % 8] + ROL(i + 2, delta[i % 8]));
		T[(6 * i + 3) % 8] = ROL(11, T[(6 * i + 3) % 8] + ROL(i + 3, delta[i % 8]));
		T[(6 * i + 4) % 8] = ROL(13, T[(6 * i + 4) % 8] + ROL(i + 4, delta[i % 8]));
		T[(6 * i + 5) % 8] = ROL(17, T[(6 * i + 5) % 8] + ROL(i + 5, delta[i % 8]));
		RK[i * 6 + 0] = T[(i * 6 + 0) % 8];
		RK[i * 6 + 1] = T[(i * 6 + 1) % 8];
		RK[i * 6 + 2] = T[(i * 6 + 2) % 8];
		RK[i * 6 + 3] = T[(i * 6 + 3) % 8];
		RK[i * 6 + 4] = T[(i * 6 + 4) % 8];
		RK[i * 6 + 5] = T[(i * 6 + 5) % 8];
	}
}

void Encrypt(int Nr, WORD *RK, BYTE *P, BYTE *C)
{
	WORD X_Round[4]; //32 * 4 =128BIT  
	WORD X_NextRound[4];

	memcpy(X_Round, P, 16);

	for (int i = 0; i < Nr; i++)
	{
		X_NextRound[0] = ROL(9, (X_Round[0] ^ RK[i * 6 + 0]) + (X_Round[1] ^ RK[i * 6 + 1]));
		X_NextRound[1] = ROR(5, (X_Round[1] ^ RK[i * 6 + 2]) + (X_Round[2] ^ RK[i * 6 + 3]));
		X_NextRound[2] = ROR(3, (X_Round[2] ^ RK[i * 6 + 4]) + (X_Round[3] ^ RK[i * 6 + 5]));
		X_NextRound[3] = X_Round[0];

		memcpy(X_Round, X_NextRound, 16);
	}

	memcpy(C, X_NextRound, 16);
}

void Decrypt(int Nr, WORD *RK, BYTE *D, BYTE *C)
{
	WORD X_Round[4];
	WORD X_NextRound[4];

	memcpy(X_Round, C, 16);

	for (int i = 0; i < Nr; i++)
	{
		X_NextRound[0] = X_Round[3];
		X_NextRound[1] = (ROR(9, X_Round[0]) - (X_NextRound[0] ^ RK[((Nr - i - 1) * 6) + 0])) ^ RK[((Nr - i - 1) * 6) + 1];
		X_NextRound[2] = (ROL(5, X_Round[1]) - (X_NextRound[1] ^ RK[((Nr - i - 1) * 6) + 2])) ^ RK[((Nr - i - 1) * 6) + 3];
		X_NextRound[3] = (ROL(3, X_Round[2]) - (X_NextRound[2] ^ RK[((Nr - i - 1) * 6) + 4])) ^ RK[((Nr - i - 1) * 6) + 5];

		memcpy(X_Round, X_NextRound, 16);
	}

	memcpy(D, X_Round, 16);
}