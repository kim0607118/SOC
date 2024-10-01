/*
#include<stdio.h>

int main() {
	unsigned long data = 0x10101;			// 0x00010101	0000 0000 0000 0001 0000 0001 0000 0001
	unsigned long msk1 = data << 12;		// 0x10101000	0001 0000 0001 0000 0001 0000 0000 0000
	unsigned long msk2 = ~msk1;				// 0xefefefff	1110 1111 1110 1111 1110 1111 1111 1111
											// 0x00010101	0000 0000 0000 0001 0000 0001 0000 0001

	printf("Result 0 = %#.8x \n", data);
	printf("Result 1 = %#.8x \n", msk1);
	printf("Result 2 = %#.8x \n", msk2);
	printf("Result 3 = %#.8x \n", data | msk1);
	return 0;
}
*/