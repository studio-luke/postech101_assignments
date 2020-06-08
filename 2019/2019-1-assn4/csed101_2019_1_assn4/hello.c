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

// 1. 종료조건
// 2. 호출 시 input 값의 변경이 있어야 함
// 3. 종료시점으로부터 발상