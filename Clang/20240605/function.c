#include <stdio.h>

int main() {
	int arr[5][6] = { 0 }; // 5�� 6���� �迭�� �����ϰ� 0���� �ʱ�ȭ
	int value = 1; // �ʱ�ȭ�� ��
	int totalSum = 0; // ��ü ���� ������ ����

	// 4�� 5�� �κ��� 1���� 20���� �ʱ�ȭ
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			arr[i][j] = value++;
			totalSum += arr[i][j]; // ��ü ���� ���
		}
	}

	// �� ���� ���� ������ ���� ����
	for (int i = 0; i < 4; i++) {
		int rowSum = 0;
		for (int j = 0; j < 5; j++) {
			rowSum += arr[i][j];
		}
		arr[i][5] = rowSum;
	}

	// �� ���� ���� ������ �࿡ ����
	for (int j = 0; j < 6; j++) {
		int colSum = 0;
		for (int i = 0; i < 4; i++) {
			colSum += arr[i][j];
		}
		arr[4][j] = colSum;
	}

	// ��ü ���� �迭�� ������ ��ҿ� ����
	arr[4][5] = totalSum;

	// ��ü �迭�� ���� ���
	printf("��ü �迭�� ��:\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}