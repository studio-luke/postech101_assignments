#include<stddef.h>
#include <stdio.h>
#include "mystring.h"

int main()
{
	char str[256] = { 0 };
	printf("%d\n", mystrlen("cs101"));
	printf("%s\n", mystrcpy(str, "Good Day")); // ���: Good Day
	printf("%s\n", mystrcpy(str, "Hello"));     // ���: Hello
	mystrcat(str, ", World");
	printf("%s\n", str); // ���: Hello, World
	printf("%s\n", mystrchr("cs101", '1')); //���101
	return 0;
}
int mystrlen(char *str)
{
	int i;
	for (i = 0; str[i] != NULL; i++);
	return i;
	// NULL ����('\0')�������ѹ��ڿ��Ǳ��̸���ȯ, ���ڿ��ǰ��0 ��ȯ
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int i = 0;

	while (fromStr[i] != NULL)
	{
		toStr[i] = fromStr[i];
		i++;
	}
	toStr[i] = NULL;

	return toStr;

	// Insert your code                     //���ڿ������Լ���NULL ���ڸ������ѹ��ڿ�fromStr �����ڿ�toStr ����������, ���ڿ�toStr�ǽ����ּҸ���ȯ�Ѵ�
}

char *mystrcat(char *str1, char *str2)
{
	int i = 0;
	int len = mystrlen(str1);

	while (str2[i] != NULL)
	{
		str1[len + i] = str2[i];
		i++;
	}

	return str1;

	// Insert your code    //���ڿ������Լ���str1 �ǳ���str2 ���̾���δ�. ��, ���ڿ�str1 ����NULL ���ڴ�str2 ��ù��°���ڷε��������str2 ��NULL ���ڴ³��´�. ���ڿ�������, ���ڿ�str1 �ǽ����ּҸ���ȯ�Ѵ�
}

char* mystrchr(char *str, char c)
{
	int i = 0;

	while (str[i] != NULL)
	{
		if (str[i] == c)
			return &str[i];
		i++;
	}
	return NULL;
	// Insert your code   //���ڿ�str��������ó������c����ġ�ϴ¹���c�ǽ����ּҸ���ȯ�Ѵ�. ���๮�ڿ�str������ġ�ϴ°��̾�����NULL����ȯ�Ѵ�
}
