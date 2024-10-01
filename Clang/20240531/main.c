#include<stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
	if (n <= 1) {
		return false; // 1 이하의 수는 소수가 아님
	}
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false; // 2부터 n의 제곱근까지 나누어 떨어지면 소수가 아님
		}
	}
	return true; // 나누어 떨어지는 수가 없으면 소수임
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