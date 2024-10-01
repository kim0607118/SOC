#include<stdio.h>

int main() {
	int h, j, i, n = 0;
	for (int j = 0; j < 6; j++) {
		for (int h = 5; h < n; h--) {
			printf(" ");
		}
		for (int i = 0; i < j; i++) {
			printf("*");
		}
		printf("\n");
	}
	for (int j = 4; j > 0; j--) {
		for (int h = 5; h < n; h--) {
			printf(" ");
		}
		for (int i = 0; i < j; i++) {
			printf("*");
		}
		printf("\n");
	}
	printf("end\n");
	return 0;
}