#pragma warning(disable : 4996)
#include <stdio.h>

#define PI 3.141592

int sum(int a);
int factorial(int n);

int main() {
	int num;
	scanf("%d", &num);
	printf("Sum Result: %d\n", sum(num));
	printf("Factorial Result: %d\n", factorial(num));
}

int sum(int a) {
	if (a == 0)
		return 0;
	else
		return a + sum(a - 1);
}

int factorial(int n) {
	if (n == 1)
		return 1;
	else
		return n * factorial(n - 1);
}

// 1. ��������
// 2. ȣ�� �� input ���� ������ �־�� ��
// 3. ����������κ��� �߻�