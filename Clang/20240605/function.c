#include <stdio.h>

int main() {
	int arr[5][6] = { 0 }; // 5행 6열의 배열을 선언하고 0으로 초기화
	int value = 1; // 초기화할 값
	int totalSum = 0; // 전체 합을 저장할 변수

	// 4행 5열 부분을 1부터 20까지 초기화
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			arr[i][j] = value++;
			totalSum += arr[i][j]; // 전체 합을 계산
		}
	}

	// 각 행의 합을 마지막 열에 저장
	for (int i = 0; i < 4; i++) {
		int rowSum = 0;
		for (int j = 0; j < 5; j++) {
			rowSum += arr[i][j];
		}
		arr[i][5] = rowSum;
	}

	// 각 열의 합을 마지막 행에 저장
	for (int j = 0; j < 6; j++) {
		int colSum = 0;
		for (int i = 0; i < 4; i++) {
			colSum += arr[i][j];
		}
		arr[4][j] = colSum;
	}

	// 전체 합을 배열의 마지막 요소에 저장
	arr[4][5] = totalSum;

	// 전체 배열의 값을 출력
	printf("전체 배열의 값:\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}