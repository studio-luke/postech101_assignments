/* Started at 4/25/2020 13:42 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH while(getchar()!='\n');

void print_info() {
	int back;
	system("cls");
	while (1) {
		printf("-------------------------- �̴� �߱� ���� ���� --------------------------\n");
		printf("\n�� ������ �߱��� ���� �Ϻ� ������ '�̴� �߱� ����'�Դϴ�.\n");
		printf("\n  1. ������ �� 3ȸ�� �̷���� �ֽ��ϴ�.\n");
		printf("\n  2. �÷��̾�� ���� Ȥ�� ���� �Ÿ� �� �ֽ��ϴ�.\n");
		printf("\n  3. ��Ÿ�� ġ�ų� ������ �Ǹ� ��� �� �� �ֽ��ϴ�.\n");
		printf("\n  4. ���ڿ� ���� �ƿ��� ������, �ö��� �ƿ�, ��Ʈ����ũ �ƿ��� �ֽ��ϴ�.\n");
		printf("\n  5. 3ȸ���� ������ ������ 10�� �̻��̸� ���ӿ��� �¸��ϰ� �˴ϴ�. \n");
		printf("--------------------------------------------------------------------------\n");
		printf("���� �޴��� ���ư���(-1):");
		scanf("%d", &back); FFLUSH;
		if (back == -1) break;
	}
}

void draw_line() {
	for (int i = 0; i < 50; i++) printf("=");
	printf("\n");
}

int print_menu() {
	char menu;
	system("cls");
	while (1){
		draw_line();
		printf("\n\t\t1. ���� ����\n");
		printf("\n\t\t2. ���� ����\n");
		printf("\n\t\t3. ���� ����\n\n");
		draw_line();

		scanf("%c", &menu); FFLUSH
		if ('1' <= menu && menu <= '3')
			return menu - '0';

		system("cls");
		printf("�޴��� �ٽ� �������ּ���.\n");
	}
}

void print_score(int cur_in, int cur_score, int fir, int sec, int thr) {
	printf("������������������������������������������������������������������������������������������������\n");
	printf("��           1ȸ   2ȸ   3ȸ     �� ��          ��\n");
	switch (cur_in) {
	case 1:
		printf(" ����       %d \n", cur_score); break;
	case 2:
		printf(" ����       %d    %d \n", fir, cur_score); break;
	case 3:
		printf(" ����       %d    %d    %d \n", fir, sec, cur_score); break;
	case 4:
		printf(" ����       %d    %d    %d       %d \n", fir, sec, thr, fir+sec+thr); break;
	}
	printf("��                                              ��\n");
	printf("������������������������������������������������������������������������������������������������\n");
}

void print_count(int ball, int strike, int out) {
	int i;
	printf("B ");
	for (i = 0; i < ball; i++) printf("��");
	for (i = 0; i < 3 - ball; i++) printf("��");
	printf("\nS ");
	for (i = 0; i < strike; i++) printf("��");
	for (i = 0; i < 2 - strike; i++) printf("��");
	printf("\nO ");
	for (i = 0; i < out; i++) printf("��");	
	for (i = 0; i < 2 - out; i++) printf("��");
	printf("\n");
}

void print_base(int one, int two, int three) {
	printf("\t        %s\n", two ? "��" : "��");
	printf("\t      ��   �� \n");
	printf("\t    ��       �� \n");
	printf("\t  ��           �� \n");
	printf("\t%s               %s \n", three ? "��" : "��", one ? "��" : "��");
	printf("\t  ��           �� \n");
	printf("\t    ��       �� \n");
	printf("\t      ��   �� \n");
	printf("\t        ��, \n");
}

int get_swing_result(int is_final, int is_strike_full) {
	int result;
	int prob = rand() % 100	+ 1;
	if (0 < prob && prob <= 14)			result = 1;	// ��Ÿ
	else if (14 < prob && prob <= 21)	result = 2;	// 2��Ÿ
	else if (21 < prob && prob <= 26)	result = 3;	// 3��Ÿ
	else if (26 < prob && prob <= 29)	result = 4;	// Ȩ��
	else if (29 < prob && prob <= 62)	result = 5;	// �ö��� �ƿ� 29~62
	else if (62 < prob && prob <= 100)	result = 6;	// ��Ʈ����ũ 62~100

	if (!(is_final && (result == 5 || is_strike_full && result == 6)))
		system("cls");

	switch (result) {
	case 1:	printf("��Ÿ�Դϴ�.\n");			break;
	case 2: printf("2��Ÿ�Դϴ�.\n");			break;
	case 3: printf("3��Ÿ�Դϴ�.\n");			break;
	case 4: printf("Ȩ���Դϴ�!!!!¦¦¦\n");	break;
	case 5: printf("�ö��� �ƿ��Դϴ�.\n");		break;
	case 6:
		if (is_strike_full)	printf("��Ʈ����ũ �ƿ�!!\n");
		else printf("��Ʈ����ũ�Դϴ�.\n");
	}
	return result;
}

int get_pass_result(int is_final, int is_strike_full, int is_ball_full) {
	int result;
	int prob = rand() % 100 + 1;
	if (0 < prob && prob <= 65)			result = 1;	// ��
	else if (65 < prob && prob <= 100)	result = 0;	// ��Ʈ����ũ

	if (!(is_final && is_strike_full && result == 0))
		system("cls");

	if (result) {
		if (is_ball_full) printf("�����Դϴ�.\n");
		else printf("���Դϴ�.\n");
	} else {
		if (is_strike_full) printf("��Ʈ����ũ �ƿ�!!\n");
		else printf("��Ʈ����ũ �Դϴ�.\n");
	}
	return result;
}

int start_inning(int num, int *fir, int *sec, int *thr, int *total) {
	char p_choice;
	int swing_result;
	int base1 = 0, base2 = 0, base3 = 0;
	int ball = 0, strike = 0, out = 0;
	int score = 0;
	int is_new_striker = 0;
	int is_final, is_finished = 0, back;

	while (1) {
		draw_line();
		printf("%dȸ\n", num);
		print_score(num, score, *fir, *sec, *thr);
		print_count(ball, strike, out);
		print_base(base1, base2, base3);
		is_final = (num >= 3 || *total + score >= 10) && out >= 2;
		printf("1. ����\t2. �Ÿ���\n");
		printf("�Է�: ");
		scanf("%c", &p_choice);	FFLUSH;


		if (p_choice == '1') {
			swing_result = get_swing_result(is_final, strike >= 2);

			is_new_striker = 1;
			switch (swing_result) {
			case 1: // ��Ÿ
				if (base3)	printf("\nȨ��! ������ �� �� �ø��ϴ�.\n");
				score += base3;
				base3 = base2;
				base2 = base1;
				base1 = 1; break;
			case 2:	// 2��Ÿ
				if (base3)	printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				if (base2)	printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				score += base2 + base3;
				base3 = base1;
				base2 = 1;
				base1 = 0; break;
			case 3:	// 3��Ÿ
				if (base3)	printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				if (base2)	printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				if (base1)	printf("\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				score += base1 + base2 + base3;
				base3 = 1;
				base2 = base1 = 0; break;
			case 4:	// Ȩ��
				if (base3)	printf("\n3�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				if (base2)	printf("\n2�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				if (base1)	printf("\n1�� ���� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				printf("\nŸ�� Ȩ��! ������ �� �� �ø��ϴ�.\n");
				score += 1 + base1 + base2 + base3;
				base3 = base2 = base1 = 0; break;
			case 5:
				out += 1; break;
			case 6:
				if (strike >= 2) out += 1;
				else {
					strike += 1;
					is_new_striker = 0;
				} break;
			}
			if (is_new_striker)
				ball = strike = 0;

		}
		else if (p_choice == '2') {
			if (get_pass_result(is_final, strike >= 2, ball >= 3)) {
				if (ball >= 3) {
					strike = ball = 0;
					if (!base1)	base1 = 1;
					else {
						if (!base2)	base2 = 1;
						else {
							base3 = 1;
							if (base3) {
								printf("Ȩ��! ������ �� �� �ø��ϴ�.\n");
								score++;
							}
						}
					}
				}
				else	ball += 1;
			}
			else {
				if (strike >= 2) {
					out += 1;
					strike = ball = 0;
				}
				else	strike += 1;
			}
		}
		else {
			system("cls");
			printf("���ڸ� �ٽ� �Է��ϼ���.\n");
		}

		if (out >= 3) {
			*total += score;
			switch (num) {
			case 1: *fir = score; break;
			case 2: *sec = score; break;
			case 3: *thr = score;
				printf("��Ⱑ ����Ǿ����ϴ�.\n");
				is_finished = 1;
			}
			if (num < 3) {
				printf("�̴��� ����Ǿ����ϴ�.\n");
				if (*total >= 10)	is_finished = 1;
			}
			if (is_finished) {
				print_score(4, 0, *fir, *sec, *thr);
				printf("* ���: �÷��̾�%s�Ͽ����ϴ�.\n", (*total >= 10) ? "�� �¸�" : "���� �й�");
				printf("���� �޴��� ���ư���(-1) ");
				scanf("%d", &back); FFLUSH;
				return 1;
			}
			return 0;
		}
	}
}
int start_game() {
	int fir = 0, sec = 0, thr = 0, total = 0;
	system("cls");
	draw_line();
	printf("������ �����մϴ�.\n");
	draw_line();
	for (int i = 1; i <= 3; i++)
		if (start_inning(i, &fir, &sec, &thr, &total))
			break;
}

int main()
{
	while (1) {
		srand(time(NULL));
		switch (print_menu()) {
		case 1: start_game(); break;
		case 2: print_info(); break;
		case 3: return 0;
		}
	}
}
