/*#include<stdio.h>

int main() {
	int sum = 0;
	char arr1[5] = "Hello";
	int arr2[5];
	int size = sizeof(arr1) / sizeof(arr1[0]);

	for (int i = 0; i < size; i++) {
		printf("input score of student %c\n", arr1[i]);
		scanf_s("%d", &arr2[i]);
		sum = sum + arr2[i];
	}
	int average = sum / size;
	for (int i = 0; i < size; i++) {
		printf("Name = %c, Score = %d\n", arr1[i], arr2[i]);
		if (arr2[i] < average) {
			printf("faiil\n");
		}
		else {
			printf("pass\n");
		}
	}
	printf("sum of score = %d\n average of score = %d\n", sum, average);
}
*/