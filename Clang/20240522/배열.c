/*
#include<stdio.h>

int main() {
	int byte_size, size = 0;
	int arr[5];

	byte_size = sizeof(arr);
	printf("size of array = %d\n", byte_size);

	size = sizeof(arr) / sizeof(arr[0]);
	printf("size of array = %d\n", size);

	for (int i = 0; i < size; i++) {
		printf("input arr[%d]\n", i);
		scanf_s("%d", &arr[i]);
	}
	for (int i = 0; i < size; i++) {
		printf("array[%d] = %d\n", i, arr[i]);
	}
}
*/