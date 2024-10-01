/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void local() {
	int count = 1;
	printf("local func calld times = %d\n", count);
	count++;
}

void staticVar() {
	static int static_count = 1;
	printf("staticvar() is runing...\ncalled %d times\n", static_count);
	static_count++;
}

int main() {
	for (int i = 0; i < 2; i++) {
		local();
		staticVar();
	}
}

int sum(x, y) {
	//지역변수
	int z = x + y;
	//정적변수
	static int d = 20;
	return z;
}

void print_hello(j) {
	for (int i = 0; i < j; i++) {
		printf("hello_world\n");
	}
}

int main() {
	int x, y, z = 0;

	//x와 y 입력받기
	printf("input x\n");
	scanf_s("%d", &x);
	printf("input y\n");
	scanf_s("%d", &y);

	//지역함수 사용하여 z값 구하기
	z = sum(x, y);
	printf("x=%d\ny=%d\nsum of x,y = %d\n",x,y,z);

	//결과값 만큼 helloworld 출력
	print_hello(z);
}
*/