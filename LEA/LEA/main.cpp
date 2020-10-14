#include "lea.h"

// LEA-128 Encrypt, Decrypt
int main()
{
	BYTE K[16] =
	{
		0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0
	};

	BYTE P[16] =
	{
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
	};

	WORD RoundKey[144] = { 0, };
	BYTE C[16] = { 0 };
	BYTE D[16] = { 0 };

	KeySchedule_128(K, RoundKey);

	printf("Key : ");
	for (int i = 0; i < 16; i++)
	{
		printf("0x%02x ", K[i]);
	}
	printf("\n\n");

	printf("Plaintext :  ");
	for (int i = 0; i < 16; i++)
	{
		printf("0x%02x ", P[i]);
	}
	printf("\n\n");

	Encrypt(24, RoundKey, P, C);
	printf("Ciphertext : ");
	for (int i = 0; i < 16; i++)
	{
		printf("0x%02x ", C[i]);
	}
	printf("\n\n");

	Decrypt(24, RoundKey, D, C);
	printf("Plaintext :  ");
	for (int i = 0; i < 16; i++)
	{
		printf("0x%02x ", D[i]);
	}
	printf("\n");

	return 0;
}

/*
// LEA-192 Encrypt, Decrypt

int main()
{
	BYTE K[24] =
	{
	0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0, 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87
	};

	BYTE P[16] =
	{
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
	};

	WORD RoundKey[168] = { 0, };
	BYTE C[16] = { 0 };
	BYTE D[16] = { 0 };

	KeySchedule_192(K, RoundKey);

	printf("Key : ");
	for (int i = 0; i < 24; i++)
	{
	printf("0x%02x ", K[i]);
	}
	printf("\n\n");

	printf("Plaintext :  ");
	for (int i = 0; i < 16; i++)
	{
	printf("0x%02x ", P[i]);
	}
	printf("\n\n");

	Encrypt(28, RoundKey, P, C);
	printf("Ciphertext : ");
	for (int i = 0; i < 16; i++)
	{
	printf("0x%02x ", C[i]);
	}
	printf("\n\n");

	Decrypt(28, RoundKey, D, C);
	printf("Plaintext :  ");
	for (int i = 0; i < 16; i++)
	{
	printf("0x%02x ", D[i]);
	}
	printf("\n");

	return 0;
}

// LEA-256 Encrypt, Decrypt
int main()
{
	BYTE K[32] =
	{
	0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0, 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e, 0x0f
	};

	BYTE P[16] =
	{
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
	};

	WORD RoundKey[192] = { 0, };
	BYTE C[16] = { 0 };
	BYTE D[16] = { 0 };

	KeySchedule_256(K, RoundKey);

	printf("Key : ");
	for (i = 0; i < 32; i++)
	{
	printf("0x%02x ", K[i]);
	}
	printf("\n\n");

	printf("Plaintext :  ");
	for (i = 0; i < 16; i++)
	{
	printf("0x%02x ", P[i]);
	}
	printf("\n\n");

	Encrypt(32, RoundKey, P, C);
	printf("Ciphertext : ");
	for (i = 0; i < 16; i++)
	{
	printf("0x%02x ", C[i]);
	}
	printf("\n\n");

	Decrypt(32, RoundKey, D, C);
	printf("Plaintext :  ");
	for (i = 0; i < 16; i++)
	{
	printf("0x%02x ", D[i]);
	}
	printf("\n");
	return 0;
}
*/