#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 30

void seperate_arr(char email[], int size, char ID[], char domain[]);
int validate_email(char ID[], char domain[], char email[], int size, int* choose); // �̸��Ϸκ��� ������ ��ġ�ϴ���, ���Ǵ� ����������, �н����尡 ��ġ�ϴ��� üũ�ϴ� �Լ� 
int make_password(char email[], int size, char system_PW[], char ID[], char domain[]); // �̸��Ϸ� ���� �н����带 �����ϴ� �Լ�
void check_PW(char PW[], char system_PW[], int* choose);
int str_size(char str[]);
void try_again(int* choose); // ���Է� �������� ����� �Լ�
//printf("��������� ��1\n");
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
	for (i = 0; i < MAX; i++) // ID �迭 �ʱ�ȭ
	{
		ID[i] = 0;
	}
	for (i = 0; i < MAX; i++) // domain �迭 �ʱ�ȭ
	{
		domain[i] = 0;
	}
	for (i = 0; i < MAX; i++) // @�� �������� ���̵�� �������� ������ �迭�� �־��ش�
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
	while (str_size(system_PW) < 10) // ��й�ȣ�� 10�ڷ� ���̴ٿ� �������� �����ư��鼭 �� ���ھ� �̿��� �����
	{
		if (ID[a] == '\0' && domain[b] == '\0') // ���̵�� ������ ���� 10���ڰ� ���� ���� ��� ������ ������ 0���� ä���
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
		if (email[a] == '@') //�̸��� ���� ����1 - @�� ���� ���
		{
			at_exist = 1;
			break;
		}
	}
	if (at_exist == 0)
	{
		is_error = 1;
	}
	if (ID[0] == '\0') //�̸��� ���� ����2 - ���̵� ���� ���
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
		if (domain[a] == '.') //�̸��� ������ ���� ����1 - . �� ���� ���
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
		if (domain[a] == '.' && domain[a + 1] == '.') // �̸��� ������ ���� ����2 - �����ο� .. �� �ִ� ���
		{
			is_error = 2;
		}
	}
	if (domain[0] == '.' || domain[str_size(domain) - 1] == '.') // �̸��� ������ ���� ����3 - �������� ���� �հ� �ڿ� .�� �ִ� ���  
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
				if (system_domain[a] == domain[a]); // �̸��� ������ �ʴ� ������ - !��� ������ txt 
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
	if (yesorno == 'y') *choose = 1; //main ȣ�� ���ϰ� ó������ ���ư��� ��?
	else *choose = 0; // ���� ���� 
}