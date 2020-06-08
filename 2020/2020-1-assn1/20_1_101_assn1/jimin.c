#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_menu(); // �ʱ� �޴� 
void print_info(); // ���� ����
void draw_line(); // �� �߱� 
void start_game(); // ���� ���� 
int start_inning(int inning, int strike, int ball, int out, int base1, int base2,
	int base3, int score, int first_score, int second_score, int third_score, int total_score); // �̴� ���� 
void print_score(int inning, int score, int first_score, int second_score, int third_score, int total_score); // ���� �����ֱ�
void print_count(int strike, int ball, int out);// ī��Ʈ ����
void print_base(int base1, int base2, int base3);// ���ڻ�Ȳ �����ֱ�
int get_swing_result();// ���� ���
int get_pass_result(); // �� or ��Ʈ����ũ

int main()
{

	print_menu();
	start_game();
}

void draw_line()
{
	int a;
	for (a = 1; a <= 50; a++)
	{
		printf("=");
	}
}

void print_info()
{
	printf("---------------------------------------------�̴� �߱� ���� ����-------------------------\n");
	printf("\n");
	printf(" �� ������ �߱��� ���� �Ϻ� ������ '�̴� �߱� ����'�Դϴ� \n");
	printf("\n");
	printf("1. ������ �� 3ȸ�� �̷���� �ֽ��ϴ�.\n");
	printf("\n");
	printf("2.�÷��̾�� ���� Ȥ�� ���� �Ÿ� �� �ֽ��ϴ�.\n");
	printf("\n");
	printf("3. ��Ÿ�� ġ�ų� ������ �Ǹ� ��� �� �� �ֽ��ϴ�.\n");
	printf("\n");
	printf("4.���ڿ� ���� �ƿ��� ������, �ö��� �ƿ�, ��Ʈ����ũ �ƿ��� �ֽ��ϴ�.\n");
	printf("\n");
	printf("5. 3ȸ���� ������ ������ 10�� �̻��̸� ���ӿ��� �¸��ϰ� �˴ϴ�.\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("���� �޴��� ���ư���(-1):");
}

void print_menu()
{
	int num = 0;
	int minus_one = 0;

	while (num != 1)
	{
		draw_line();
		printf("\n");
		printf("             1. ���� ����\n");
		printf("             2. ���� ����\n");
		printf("             3. ���� ����\n");
		printf("\n");
		draw_line();
		printf("\n");
		printf("�����ϰ��� �ϴ� �޴��� �Է��ϼ���:");

		scanf("%d", &num);
		switch (num)
		{
		case 1:
			break;

		case 2:
			while (minus_one != -1)
			{

				system("cls");
				print_info();
				scanf("%d", &minus_one);
			}
			minus_one = 0;
			system("cls");
			break;
		case 3:
			printf("���α׷��� �����մϴ�.");
			return 0;
			break;

		default:
			system("cls");
			printf("�޴��� �ٽ� �������ּ���.\n");
		}
	}
}  // print_menu ��

int get_swing_result()
{
	srand(time(NULL));
	int swing_random = rand() % 100;

	if (0 <= swing_random && swing_random < 14)
		return 1;
	else if (14 <= swing_random && swing_random < 21)
		return 2;
	else if (21 <= swing_random && swing_random < 26)
		return 3;
	else if (26 <= swing_random && swing_random < 29)
		return 4;
	else if (29 <= swing_random && swing_random < 62)
		return 5;
	else
		return 6;

}//1- 1��Ÿ , 2- 2��Ÿ , 3-3��Ÿ , 4-Ȩ�� , 5-�ö��� �ƿ� 6- ��Ʈ����ũ 

int get_pass_result()
{
	srand(time(NULL));
	int ball_random = rand() % 100;

	if (0 <= ball_random && ball_random < 65)
		return 7;

	else
		return 6;

} // 6 ��Ʈ����ũ, 7 ��

void print_score(int inning, int score, int first_score, int second_score, int third_score, int total_score)
{
	printf(" ��--------------------------------------------------------��\n");
	printf(" ��               1ȸ     2ȸ    3ȸ        ����           ��\n");
	switch (inning)
	{
	case 1:
		printf("  ����            %d                                        \n ", first_score);
		break;
	case 2:
		printf("  ����            %d     %d                                    \n ", first_score, second_score);
		break;
	case 3:
		printf("  ����            %d     %d     %d                               \n ", first_score, second_score, third_score);
		break;
	default:
		total_score = first_score + second_score + third_score;
		printf("  ����            %d     %d     %d          %d            \n", first_score, second_score, third_score, total_score);
	}
	printf("��                                                        ��\n");
	printf(" ��--------------------------------------------------------��\n");

}


int start_inning(int inning, int strike, int ball, int out, int base1,
	int base2, int base3, int score, int first_score, int second_score, int third_score, int total_score)// ��ŸƮ�̴�
{

	int swing_or_not;


	while (out < 3)
	{

		draw_line();
		printf("\n \n");
		draw_line();
		printf("\n");
		printf("%d ȸ", inning);
		printf("\n");
		print_score(inning, score, first_score, second_score, third_score, total_score); // ���� �����ֱ�
		print_count(strike, ball, out);// ī��Ʈ ����
		print_base(base1, base2, base3);// ���ڻ�Ȳ �����ֱ�
		printf("\n 1. ����  2.  �Ÿ��� \n�Է�: ");
		scanf(" %d ", &swing_or_not);

		switch (swing_or_not)
		{
		case 1: // ������ ��� 

			if (get_swing_result() == 1) //1��Ÿ
			{
				printf("��Ÿ�Դϴ�.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3�� ���� ���� ��
				{
					score = score + 1;
					base3 = 0;
					printf("\n\nȨ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base2 == 1)//2�� ���� ���� �� 
				{
					base3 = 1;
					base2 = 0;
				}
				if (base1 == 1)//1�� ���� ���� ��
				{
					base2 = 1;
					base1 = 0;
				}
				base1 = 1;
			}
			else if (get_swing_result() == 2)  // 2��Ÿ
			{
				printf("2��Ÿ �Դϴ�.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3�� ���� ���� ��
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base2 == 1)//2�� ���� ���� �� 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base1 == 1)//1�� ���� ���� ��
				{
					base3 = 1;
					base1 = 0;
				}
				base2 = 1;
			}

			else if (get_swing_result() == 3)  // 3��Ÿ
			{
				printf("3��Ÿ �Դϴ�.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3�� ���� ���� ��
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base2 == 1)//2�� ���� ���� �� 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base1 == 1)//1�� ���� ���� ��
				{
					score = score + 1;
					base1 = 0;
					printf("\n\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				base3 = 1;
			}


			else if (get_swing_result() == 4) // Ȩ��
			{
				printf("Ȩ���Դϴ�.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3�� ���� ���� ��
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base2 == 1)//2�� ���� ���� �� 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				if (base1 == 1)//1�� ���� ���� ��
				{
					score = score + 1;
					base1 = 0;
					printf("\n\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�. ");
				}
				score = score + 1;
				printf("\n\nŸ�� Ȩ��! ������ �� �� �ø��ϴ�.");
			}
			else if (get_swing_result() == 5) // �ö��� �ƿ�
			{
				strike = 0; ball = 0;
				out = out + 1;
				printf("�ö��� �ƿ��Դϴ�. \n");
			}
			else // ���� �� ��Ʈ����ũ
			{
				strike = strike + 1;
				if (strike == 3)
				{
					out = out + 1;
					strike = 0;
					ball = 0;
					printf("��Ʈ����ũ �ƿ�!!\n");
				}
				else
				{
					printf("��Ʈ����ũ �Դϴ�.\n");
				}
			}
			break;

		case 2: // �Ÿ��� ���ý�
			if (get_pass_result == 6) // �Ÿ��� �� ��Ʈ����ũ
			{
				strike = strike + 1;
				if (strike == 3)
				{
					out = out + 1;
					strike = 0;
					ball = 0;
					printf("��Ʈ����ũ �ƿ�!!\n");
				}
				else
				{
					printf("��Ʈ����ũ �Դϴ�. \n");

				}
			}
			else
			{
				ball = ball + 1;
				if (ball == 4)
				{
					strike = 0; ball = 0;
					printf("�����Դϴ� \n.");
					if (base1 == 0) // 1�翡 ���� �� 
					{
						base1 = 1;
					}
					else if (base1 == 1) // 1�翡 ���� ��
					{
						if (base2 == 1)
						{
							if (base3 == 1) // ���� ����
							{
								score = score + 1;
							}
							else // ���� 1,2 �� 
							{
								base3 = 1;
							}

						}
						else // 1�翡 �ְ� 2�翡 ���� ��
						{
							base2 = 1;

						}

					}

				}
				else
				{
					printf("���Դϴ�. \n");
				}

			}
			break;
		default: // 1�� 2�� �ƴ� �ٸ� �� ������ ��
			printf("���ڸ� �ٽ� �Է��Ͻʽÿ�.\n");
		}

	}

	strike = 0; ball = 0; out = 0; base1 = 0; base2 = 0; base3 = 0;


	printf("�̴��� ����Ǿ����ϴ�.\n");

	return score;
}

void start_game()
{

	int inning = 1;
	int strike = 0;
	int ball = 0;
	int out = 0;
	int base1 = 0;
	int base2 = 0;
	int base3 = 0;
	int score = 0;
	int first_score = 0;
	int second_score = 0;
	int third_score = 0;
	int total_score = 0;

	draw_line();
	printf("\n������ �����մϴ�.\n");

	while (inning <= 3)
	{
		start_inning(inning, strike, ball, out, base1, base2,
			base3, score, first_score, second_score, third_score, total_score);


		if (inning == 1)
			first_score = score;
		else if (inning == 2)
			second_score = score;
		else if (inning == 3)
			third_score = score;

		inning = inning + 1;

		score = 0;

	}


}

void print_base(int base1, int base2, int base3)
{
	printf("\n");
	switch (base1)
	{
	case 0:
		if (base2 == 0)
		{
			if (base3 == 0) // ���� ���� 
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
			else  //���� 3�� 
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
		}
		else
		{
			if (base3 == 0) // ���� 2��
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");

			}
			else // ���� 2,3��
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
		}

		break;
	case 1:
		if (base2 == 0)
		{
			if (base3 == 0) // ���� 1��
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
			else  //���� 1, 3�� 
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
		}
		else
		{
			if (base3 == 0) // ���� 1, 2��
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");

			}
			else // ���� ����
			{
				printf("              ��              \n");
				printf("           ��    ��           \n");
				printf("       ��            ��       \n");
				printf("   ��                    ��   \n");
				printf("��                          ��\n");
				printf("   ��                    ��   \n");
				printf("       ��            ��       \n");
				printf("           ��    ��           \n");
				printf("              ��              \n");
			}
		}
	}
}

void print_count(int strike, int ball, int out)
{
	printf("\n");
	switch (ball)
	{
	case 0:
		printf("B �ۡۡ�\n");
		break;
	case 1:
		printf("B �ܡۡ�\n");
		break;
	case 2:
		printf("B �ܡܡ�\n");
		break;
	case 3:
		printf("B �ܡܡ�\n");
		break;

	}
	switch (strike)
	{
	case 0:
		printf("S �ۡ�\n");
		break;
	case 1:
		printf("S �ܡ�\n");
		break;
	case 2:
		printf("S �ܡ�\n");
		break;

	}
	switch (out)
	{
	case 0:
		printf("O �ۡ�\n");
		break;
	case 1:
		printf("O �ܡ�\n");
		break;
	case 2:
		printf("O �ܡ�\n");
		break;

	}

}