#include<stdio.h>
#include"mystring.h"

int main()
{
	char str[256];
	printf("%d\n", mystrlen("cs101")); // 결과: 5
	printf("%s\n", mystrcpy(str, "Good Day")); // 결과: Good Day
	printf("%s\n", mystrcpy(str, "Hello")); // 결과: Hello
	printf("%d\n", mystrcmp("csed101", "csed103")); // 결과: -1
	printf("%d\n", mystrcmp("csed", "Csed")); // 결과: 1
	printf("%d\n", mystrcmp("csed", "cse")); // 결과: 1
	printf("%d\n", mystrcmp("csed", "csed103")); // 결과: -1
	printf("%d\n", mystrcmp("csed", "csed")); // 결과: 0
	mystrcat(str, ", World!");
	printf("%s\n", str); // 결과: Hello, World!

	return 0;
}

int mystrlen(char *str)
{
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int length = mystrlen(fromStr);
	int i;

	//toStr = malloc((length + 1) * sizeof(char));

	for (i = 0; i <= length; i++)
		toStr[i] = fromStr[i];

	return toStr;
}

int mystrcmp(char *str1, char *str2)
{
	int i = 0;

	while (1) {
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
		else if (str1[i] == NULL && str2[i] == NULL)
			return 0;
		i++;
	}
}

char *mystrcat(char *str1, char *str2)
{
	int str1_length = mystrlen(str1);
	int str2_length = mystrlen(str2);
	int i;

	for (i = 0; i <= str2_length; i++) {
		str1[i + str1_length] = str2[i];
	}

	return str1;
}
