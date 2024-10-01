#include<stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
	if (n <= 1) {
		return false; // 1 ������ ���� �Ҽ��� �ƴ�
	}
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false; // 2���� n�� �����ٱ��� ������ �������� �Ҽ��� �ƴ�
		}
	}
	return true; // ������ �������� ���� ������ �Ҽ���
}

int main(void) {
	int num,i,b = 0;
	printf("input number over 2\n");
	scanf_s("%d", &num);
		for (i = 0; i < num; i++) {
			if (isPrime(i)) {
				printf("%d\t", i);
			}
			if (i % 5 == 0) {
				printf("\n");
			}
		}
}