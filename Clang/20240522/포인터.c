/*#include<stdio.h>

int main() {
	int arr[5] = { 1,2,3,4,5 };
	int *parr;
	parr = &arr[0];

	for (int i = 0; i < 5; i++) {
		printf("arr[%d] adress : %p\n", i, &arr[i]);
		printf("(parr+%d) value : %p\n", i, (parr + i));
		if (&arr[i] == (parr + i)) {
			printf("correct\n");
		}
		else {
			printf("unmatch\n");
		}
	}

	printf("arr = %p\n", arr);
	printf("arr[0] : %p\n", &arr[0]);

	printf("size of arr = %d\n", sizeof(arr));
	printf("size of parr = %d\n", sizeof(parr));
}
*/