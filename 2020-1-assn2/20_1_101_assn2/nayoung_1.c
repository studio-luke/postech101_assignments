#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 30

void seperate_arr(char email[], int size, char ID[], char domain[]);
int validate_email(char ID[], char domain[], char email[], int size, int* choose); // 이메일로부터 형식이 일치하는지, 허용되는 도메인인지, 패스워드가 일치하는지 체크하는 함수 
int make_password(char email[], int size, char system_PW[], char ID[], char domain[]); // 이메일로 부터 패스워드를 생성하는 함수
void check_PW(char PW[], char system_PW[], int* choose);
int str_size(char str[]);
void try_again(int* choose); // 재입력 받을건지 물어보는 함수
//printf("여기까지는 됨1\n");
//matone@postech.ac.kr

char main()
{
	int choose = 1;
	char email[MAX];
	char PW[MAX];
	char system_PW[MAX] = { '\0' };
	char ID[MAX] = { '\0' };
	char domain[MAX] = { '\0' };

	while (choose == 1)
	{
		printf("\n");
		printf("---LOGIN TO ACCESS HEA SYSTEM---\n");
		printf("\n");
		printf("email : ");
		scanf("%s", email);
		seperate_arr(email, MAX, ID, domain);
		printf("password :");
		scanf("%s", PW);
		printf("\n");
		printf("--------------CHECKING--------------\n");
		if (validate_email(ID, domain, email, MAX, &choose))
		{
			make_password(email, MAX, system_PW, ID, domain);
			check_PW(PW, system_PW, &choose);
		}
	}
}

void seperate_arr(char email[], int size, char ID[], char domain[])
{
	int i = 0;
	for (i = 0; i < MAX; i++) // ID 배열 초기화
	{
		ID[i] = 0;
	}
	for (i = 0; i < MAX; i++) // domain 배열 초기화
	{
		domain[i] = 0;
	}
	for (i = 0; i < MAX; i++) // @를 기준으로 아이디와 도메인을 각각의 배열로 넣어준다
	{
		if (email[i] == '@') break;
		ID[i] = email[i];
	}
	for (int j = i + 1; j < MAX; j++)
	{
		if (email[j] == '\0') break;
		domain[j - i - 1] = email[j];
	}
}

int make_password(char email[], int size, char system_PW[], char ID[], char domain[])
{
	int i = 0;
	int a = 0, b = 0;
	while (str_size(system_PW) < 10) // 비밀번호는 10자로 아이다와 도메인을 번갈아가면서 한 글자씩 이용해 만든다
	{
		if (ID[a] == '\0' && domain[b] == '\0') // 아이디와 도메인 합이 10글자가 넘지 않을 경우 부족한 공간은 0으로 채운다
		{
			system_PW[i] = '0';
			i++;
		}
		if (ID[a] != '\0')
		{
			system_PW[i] = ID[a];
			i++;
			a++;
		}
		if (domain[b] != '\0')
		{
			system_PW[i] = domain[b];
			i++;
			b++;
		}
	}
}

int validate_email(char ID[], char domain[], char email[], int size, int* choose)
{
	int at_exist = 0;
	int dot_exist = 0;
	int is_error = 3;
	int a = 0;
	int i = 0;
	int number;
	char system_domain[20];
	FILE* infile;

	for (a = 0; a < MAX; a++)
	{
		if (email[a] == '@') //이메일 형식 에러1 - @가 없는 경우
		{
			at_exist = 1;
			break;
		}
	}
	if (at_exist == 0)
	{
		is_error = 1;
	}
	if (ID[0] == '\0') //이메일 형식 에러2 - 아이디가 없는 경우
	{
		is_error = 1;
	}
	if (is_error == 1)
	{
		printf("ERROR! invalid email format!\n");
		try_again(choose);
		return 0;
	}
	for (a = 0; a < MAX; a++)
	{
		if (domain[a] == '.') //이메일 도메인 형식 에러1 - . 이 없는 경우
		{
			dot_exist = 1;
			break;
		}
	}
	if (dot_exist == 0)
	{
		is_error = 2;
	}
	for (a = 0; a < MAX - 1; a++)
	{
		if (domain[a] == '.' && domain[a + 1] == '.') // 이메일 도메인 형식 에러2 - 도메인에 .. 이 있는 경우
		{
			is_error = 2;
		}
	}
	if (domain[0] == '.' || domain[str_size(domain) - 1] == '.') // 이메일 도메인 형식 에러3 - 도메인의 가장 앞과 뒤에 .이 있는 경우  
	{
		is_error = 2;
	}
	if (is_error == 2)
	{
		printf("ERROR! invalid domain format!\n");
		try_again(choose);
		return 0;
	}
	infile = fopen("allowed_domain.txt", "r");
	fscanf(infile, "%d", &number);
	for (i = 0; i < number; i++)
	{
		fscanf(infile, "%s", system_domain);
		int x = str_size(system_domain);
		int y = str_size(domain);
		printf("%d %d\n", x, y);

		if (x == y)
		{
			for (a = 0; a < x; a++)
			{
				printf(" %c %c \n", system_domain[a], domain[a]);
				if (system_domain[a] == domain[a]); // 이메일 허용되지 않는 도메인 - !허용 도메인 txt 
			}
			is_error = 0;
			break;
			printf("%d\n", is_error);
		}
		else
		{
			is_error = 3;
		}
	}
	if (is_error == 3)
	{
		printf("ERROR! This domain is not allowed!\n");
		try_again(choose);
		return 0;
	}
	return 1;
}

void check_PW(char PW[], char system_PW[], int* choose)
{
	for (int a = 0; a < 10; a++)
	{
		if (PW[a] == system_PW[a]);
		else
		{
			printf("ERROR! invalid password!\n");
			try_again(choose);
			return;
		}
	}
	printf("SUCCESS! now you can access HEA system!\n");
}

int str_size(char str[])
{
	int size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return  size;
}

void try_again(int* choose)
{
	char yesorno;
	while (getchar() != '\n');
	printf("\n");
	printf("Do you want try again? (y/n)");
	scanf("%c", &yesorno);
	if (yesorno == 'y') *choose = 1; //main 호출 안하고 처음으로 돌아가는 법?
	else *choose = 0; // 게임 종료 
}