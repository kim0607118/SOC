#include<stdio.h>
#include<stdlib.h>

int main(void) {
	float ft = 1.23456789123456789;
	double db = 1.23456789123456789;
	printf("%.20f\n",ft);
	printf("%.20lf\n",db);
	return 0;
}