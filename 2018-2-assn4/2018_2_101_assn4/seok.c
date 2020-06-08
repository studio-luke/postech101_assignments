#include<stddef.h>
#include <stdio.h>
#include "mystring.h"

int main()
{
	char str[256] = { 0 };
	printf("%d\n", mystrlen("cs101"));
	printf("%s\n", mystrcpy(str, "Good Day")); // 결과: Good Day
	printf("%s\n", mystrcpy(str, "Hello"));     // 결과: Hello
	mystrcat(str, ", World");
	printf("%s\n", str); // 결과: Hello, World
	printf("%s\n", mystrchr("cs101", '1')); //결과101
	return 0;
}
int mystrlen(char *str)
{
	int i;
	for (i = 0; str[i] != NULL; i++);
	return i;
	// NULL 문자('\0')를제외한문자열의길이를반환, 빈문자열의경우0 반환
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

	// Insert your code                     //문자열복사함수로NULL 문자를포함한문자열fromStr 를문자열toStr 에복사한후, 문자열toStr의시작주소를반환한다
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

	// Insert your code    //문자열연결함수로str1 의끝에str2 를이어붙인다. 즉, 문자열str1 뒤의NULL 문자는str2 의첫번째문자로덮어씌워지고str2 의NULL 문자는남는다. 문자열연결후, 문자열str1 의시작주소를반환한다
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
	// Insert your code   //문자열str에서가장처음으로c와일치하는문자c의시작주소를반환한다. 만약문자열str에서일치하는것이없으면NULL을반환한다
}
