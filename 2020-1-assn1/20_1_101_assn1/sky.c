#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable:4996)
int print_menu();
void draw_line();
void print_info();
int start_game();
int start_inning(int NR, int* R1sc, int* R2sc, int* R3sc);
void print_score(int NR, int R1, int R2, int R3);
void print_count(int ball, int strike, int out);
void print_base(int base1, int base2, int base3);
int get_swing_result();
int get_pass_result(int* ball);
int ball_advance(int* base1, int* base2, int* base3);
int single_advance(int* base1, int* base2, int* base3);
int double_advance(int* base1, int* base2, int* base3);
int triple_advance(int* base1, int* base2, int* base3);
int home_run(int* base1, int* base2, int* base3);
int main() {
	srand(time(NULL));
	int menu;
	while (1) {
		menu = print_menu();
		switch (menu) {
		case 1:
			system("cls");
			start_game();
			system("cls");
			break;
		case 2:
			print_info();
			break;
		case 3:
			printf("������ �����մϴ�.\n");
			return 0;
		default:
			system("cls");
			printf("�޴��� �ٽ� �������ּ���.\n");
		}
	}
}
void print_info() {
	system("cls");
	printf("--------------------------�̴� �߱� ���� ����--------------------------\n");
	printf("�� ������ �߱��� ���� �Ϻ� ������ '�̴� �߱� ����'�Դϴ�.\n\n");
	printf("1. ������ �� 3ȸ�� �̷���� �ֽ��ϴ�.\n\n");
	printf("2. �÷��̾�� ���� Ȥ�� ���� �Ÿ� �� �ֽ��ϴ�.\n\n");
	printf("3. ��Ÿ�� ġ�ų� ������ �Ǹ� ��� �� �� �ֽ��ϴ�.\n\n");
	printf("4. ���ڿ� ���� �ƿ��� ������, �ö��� �ƿ�, ��Ʈ����ũ �ƿ��� �ֽ��ϴ�.\n\n");
	printf("5. 3ȸ���� ������ ������ 10�� �̻��̸� ���ӿ��� �¸��ϰ� �˴ϴ�.\n");
	printf("-----------------------------------------------------------------------\n");
	printf("���� �޴��� ���ư���(-1):");
	int goto_menu;
	scanf("%d", &goto_menu);
	while (1) {
		if (goto_menu != -1) {
			printf("�߸� �Է��ϼ̽��ϴ�. ���� �޴��� ���ư���(-1):");
			scanf("%d", &goto_menu);
		}
		else {
			system("cls");
			return;
		}
	}
}
int print_menu() {
	int menu;
	draw_line();
	printf("\n\t\t1. ���� ����\n\n\t\t2. ���� ����\n\n\t\t3. ���� ����\n\n");
	draw_line();
	printf("�����ϰ��� �ϴ� �޴��� �Է��ϼ���: ");
	scanf("%d", &menu);
	return menu;
}
void draw_line() {
	int i;
	for (i = 1; i <= 50; i++)
		printf("=");
	printf("\n");
}
int start_game() {
	int i = 1, end = 0, R1sc = 0, R2sc = 0, R3sc = 0, goto_menu = 0;
	draw_line();
	printf("������ �����մϴ�.\n");
	draw_line();
	printf("\n");
	while (i <= 3) {
		end = start_inning(i, &R1sc, &R2sc, &R3sc);
		i++;
		printf("�̴��� ����Ǿ����ϴ�.\n");
		if (end == 10)
			break;
	}
	printf("\n��Ⱑ ����Ǿ����ϴ�.\n");
	draw_line();
	print_score(0, R1sc, R2sc, R3sc);
	(R1sc + R2sc + R3sc >= 10) ? printf("-���: �÷��̾ �¸��Ͽ����ϴ�.\n") : (printf("-���: �÷��̾ �й��Ͽ����ϴ�.\n"));
	printf("���� �޴��� ���ư���(-1):");
	scanf("%d", &goto_menu);
	return goto_menu;
}
int start_inning(int NR, int* R1sc, int* R2sc, int* R3sc) {
	int player_choice, pass, swing, ball = 0, strike = 0, out = 0, base1 = 0, base2 = 0, base3 = 0, score = 0;
	while (1) {
		draw_line();
		printf("%dȸ\n", NR);
		print_score(NR, *R1sc, *R2sc, *R3sc);
		print_count(ball, strike, out);
		print_base(base1, base2, base3);
		printf("1. ����, 2. �Ÿ���\n");
		printf("�Է�:");
		scanf("%d", &player_choice);
		system("cls");
		if (player_choice == 1) {
			swing = get_swing_result();
			switch (swing) {
			case 4:
				out += 1, strike = ball = 0;
				printf("�ö��� �ƿ�!!\n");
				if (out == 3)
					return (*R1sc + *R2sc + *R3sc >= 10) ? (10) : (0);
				break;
			case 0:
				if (strike < 2) {
					strike += 1;
					printf("��Ʈ����ũ �Դϴ�.\n");
				}
				else {
					out += 1;
					printf("��Ʈ����ũ �ƿ�!!\n");
					if (out == 3)
						return (*R1sc + *R2sc + *R3sc >= 10) ? (10) : (0);
					ball = strike = 0;
				}
				break;
			case 1:
				strike = ball = 0;
				printf("��Ÿ�Դϴ�\n");
				score += single_advance(&base1, &base2, &base3);
				break;
			case 2:
				strike = ball = 0;
				printf("2��Ÿ �Դϴ�.\n");
				score += double_advance(&base1, &base2, &base3);
				break;
			case 3:
				strike = ball = 0;
				printf("3��Ÿ �Դϴ�.\n");
				score += triple_advance(&base1, &base2, &base3);
				break;
			case 10:
				strike = ball = 0;
				printf("Ȩ�� �Դϴ�.\n");
				score += home_run(&base1, &base2, &base3);
				break;
			}
		}
		else if (player_choice == 2) {
			pass = get_pass_result(&ball);
			if (ball == 4) {
				ball = strike = 0;
				printf("�����Դϴ�.\n");
				base1 += 1;
				if (ball_advance(&base1, &base2, &base3) == 1) {
					printf("Ȩ��! ������ �� �� �ø��ϴ�.\n");
					score += 1;
				}
			}
			if (pass == 0) {
				if (strike < 2) {
					strike += 1;
					printf("��Ʈ����ũ �Դϴ�.\n");
				}
				else {
					out += 1;
					printf("��Ʈ����ũ �ƿ�!!\n");
					if (out == 3)
						return (*R1sc + *R2sc + *R3sc >= 10) ? (10) : (0);
					ball = strike = 0;
				}
			}
		}
		else
			printf("�ٽ� �Է����ּ���.\n");
		if (NR == 1)
			*R1sc = score;
		else if (NR == 2)
			*R2sc = score;
		else
			*R3sc = score;
	}
}
void print_score(int NR, int R1, int R2, int R3) {
	printf("\n");
	printf("����������������������������������������������������������������������������������������\n");
	printf("��         1ȸ   2ȸ   3ȸ         ����     ��\n");
	if (NR == 1)
		printf("  ����     %d\n", R1);
	else if (NR == 2)
		printf("  ����     %d     %d\n", R1, R2);
	else if (NR == 3)
		printf("  ����     %d     %d     %d\n", R1, R2, R3);
	else
		printf("  ����     %d     %d     %d           %d\n", R1, R2, R3, R1 + R2 + R3);
	printf("��                                          ��\n");
	printf("����������������������������������������������������������������������������������������\n");
}
void print_count(int ball, int strike, int out) {
	printf("B %s%s%s\n", (ball >= 1) ? ("��") : ("��"), (ball >= 2) ? ("��") : ("��"), (ball >= 3) ? ("��") : ("��"));
	printf("S %s%s\n", (strike >= 1) ? ("��") : ("��"), (strike >= 2) ? ("��") : ("��"));
	printf("O %s%s\n", (out >= 1) ? ("��") : ("��"), (out >= 2) ? ("��") : ("��"));
}
void print_base(int base1, int base2, int base3) {
	printf("                %s\n", (base2 == 1) ? ("��") : ("��"));
	printf("             ��     ��\n");
	printf("         ��             ��\n");
	printf("     ��                     ��\n");
	printf("   %s                          %s\n", (base3 == 1) ? ("��") : ("��"), (base1 == 1) ? ("��") : ("��"));
	printf("     ��                     ��\n");
	printf("         ��             ��\n");
	printf("             ��     ��\n");
	printf("                 ��\n");
}
int get_swing_result() {
	int p = rand() % 100;
	if (p < 14)
		return 1;
	else if (p < 21)
		return 2;
	else if (p < 26)
		return 3;
	else if (p < 29)
		return 10;
	else if (p < 62)
		return 4;
	else
		return 0;
}
int get_pass_result(int* ball) {
	int bors = rand() % 100;
	if (bors < 65) {
		system("cls");
		printf("���Դϴ�.\n");
		*ball += 1;
		return 1;
	}
	else
		return 0;
}
int ball_advance(int* base1, int* base2, int* base3) {
	if (*base1 == 2) {
		*base1 -= 1;
		*base2 += 1;
	}
	if (*base2 == 2) {
		*base2 -= 1;
		*base3 += 1;
	}
	if (*base3 == 2) {
		*base3 -= 1;
		return 1;
	}
	return 0;
}
int single_advance(int* base1, int* base2, int* base3) {
	int re = 0;
	if (*base3 == 1) {
		*base3 -= 1;
		printf("\nȨ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base2 == 1) {
		*base2 -= 1;
		*base3 += 1;
	}
	if (*base1 == 1) {
		*base1 -= 1;
		*base2 += 1;
	}
	*base1 += 1;
	return re;
}
int double_advance(int* base1, int* base2, int* base3) {
	int re = 0;
	if (*base3 == 1) {
		*base3 -= 1;
		printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base2 == 1) {
		*base2 -= 1;
		printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base1 == 1) {
		*base1 -= 1;
		*base3 += 1;
	}
	*base2 += 1;
	return re;
}
int triple_advance(int* base1, int* base2, int* base3) {
	int re = 0;
	if (*base3 == 1) {
		*base3 -= 1;
		printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base2 == 1) {
		*base2 -= 1;
		printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base1 == 1) {
		*base1 -= 1;
		printf("\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	*base3 += 1;
	return re;
}
int home_run(int* base1, int* base2, int* base3) {
	int re = 0;
	if (*base3 == 1) {
		*base3 -= 1;
		printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base2 == 1) {
		*base2 -= 1;
		printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	if (*base1 == 1) {
		*base1 -= 1;
		printf("\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
		re += 1;
	}
	printf("\nŸ�� Ȩ��! ������ �� �� �ø��ϴ�.\n");
	return re + 1;
}