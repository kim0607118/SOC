#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

int main(void) {
	int a = 10; //0110
	int b = 12; //1100

	printf("a&b : %d\n", a & b);	//0100
	printf("a^b : %d\n", a ^ b);	//0110
	printf("a|b : %d\n", a | b);	//1110

	return 0;
}