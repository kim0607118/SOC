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
	//��������
	int z = x + y;
	//��������
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

	//x�� y �Է¹ޱ�
	printf("input x\n");
	scanf_s("%d", &x);
	printf("input y\n");
	scanf_s("%d", &y);

	//�����Լ� ����Ͽ� z�� ���ϱ�
	z = sum(x, y);
	printf("x=%d\ny=%d\nsum of x,y = %d\n",x,y,z);

	//����� ��ŭ helloworld ���
	print_hello(z);
}
*/