#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define FFLUSH while(getchar()!='\n')

int show_menu();
int print_tutorial();
void start_game();
void show_table(int round, int comp_score, int user_score,
	char user_main_card, int user_remain_citizen);
char get_user_card(int round, int comp_score, int user_score, char user_set,
	char *user_main_card, char *user_remain_citizen);
char get_computer_card(char user_set, char *comp_main_card, char *comp_remain_citizen);
int compare_card(user_choice, comp_choice);
int cal_score(int user_victory, char user_set);

int main()
{
	int menu;
	srand(time(NULL));

	while (1) {
		menu = show_menu();		// �ʱ� �޴� ���

		switch (menu) {
		case 1:
			print_tutorial(); break;
		case 2:
			start_game(); break;
		default:
			printf("���α׷��� �����մϴ�...(Press Enter)\n");
			FFLUSH;
			return 0;
		}
	}
}

int show_menu()
{
	int command;

	while (1) {
		system("cls");
		printf("++++++++++++ E - Card ++++++++++++\n\n");
		printf("           1. ���� ����\n\n");
		printf("           2. ���� ����\n\n");
		printf("           3. ���� ����\n\n");
		printf("++++++++++++++++++++++++++++++++++\n");
		printf("�Է�: ");
		scanf("%d", &command); FFLUSH;
		if (command == 1 || command == 2 || command == 3) break;
		printf("�ùٸ� �޴��� �����ϼ���...\n");
		Sleep(1000);
	}
	
	return command;
}

int print_tutorial()
{
	system("cls");
	printf("\n++++++++++++ E - Card ���� ���� ++++++++++++\n");
	printf("\n�� ������ ���ڹ��÷� ī������ E - Card ������ ������� �Ѵ�.\n");
	printf("\n1. �� �÷��̾�� Ȳ���п� �뿹�� �� �ϳ��� �и� ���� �����Ѵ�.\n");
	printf("Ȳ���� = Ȳ�� ī�� 1�� + �ù� ī�� 4�� \n");
	printf("�뿹�� = �뿹 ī�� 1�� + �ù� ī�� 4�� \n");
	printf("\n2. �� ����ڴ� �� �ϸ��� �� ���� ī�带 �� ���̰� ���а�, �Բ� �����´�.\n");
	printf("\n3.�Ʒ��� ī�� �� �� ���迡 ���� ���и� �����Ѵ�.\n");
	printf("��, �� �÷��̾ �ù� ī�带 �´ٸ�, ���ºη� ó���Ѵ�.\n");
	printf("\n4. ���о��� ī��� �Ҹ�ǰ�, ���а� ������ ������ 2�� ���ư� �ݺ��Ѵ�.\n");
	printf("\n�󼺰���: Ȳ�� > �ù� > �뿹 > Ȳ��\n");
	printf("\n+++++++++++++++++++++++++++++++++++++++++++\n");
	printf("�޴��� ���ư����� EnterŰ�� �Է��ϼ���...");
	FFLUSH;
}

void start_game() {

	int choice;
	int round = 1;
	int comp_score = 0, user_score = 0, user_score_gain;
	char user_set;
	char comp_main_card, user_main_card;
	int comp_remain_citizen, user_remain_citizen;
	char comp_choice, user_choice;
	int victory;
	char replay;
	int game_end;

	while (1) {
		while (1) {
			game_end = 0;
			system("cls");
			printf("[����Ƚ��:  %d. ��ǻ��: %d��, ��: %d��]\n\n", round, comp_score, user_score);
			printf("[ī�� �� ����]\n");
			printf("++++++++++++++++++++++++++++++++++\n\n");
			printf("0. Ȳ���� (Ȳ�� 1��, �ù� 4��)\n\n");
			printf("1. �뿹�� (�뿹 1��, �ù� 4��)\n\n");
			printf("++++++++++++++++++++++++++++++++++\n");
			printf("�Է�: ");
			scanf("%d", &choice); FFLUSH;
			if (choice == 0 || choice == 1) break;
			printf("�ùٸ� �޴��� �����ϼ���...\n");
			Sleep(1000);
		}

		if (choice == 0) {
			user_set = 'E';
			user_main_card = 'E';
			comp_main_card = 'S';
		}
		else {
			user_set = 'S';
			user_main_card = 'S';
			comp_main_card = 'E';
		}

		comp_remain_citizen = 4;
		user_remain_citizen = 4;

		while (1) {
			if (game_end) break;
			show_table(round, comp_score, user_score, user_main_card, user_remain_citizen);
			user_choice = get_user_card(round, comp_score, user_score, user_set,
				&user_main_card, &user_remain_citizen);
			comp_choice = get_computer_card(user_set, &comp_main_card, &comp_remain_citizen);

			printf("[���� ���]\n");
			printf("+++++++++++++++++++++++++++\n\n");
			printf("* ���� ī��\t\t: ");
			switch (user_choice) {
			case 'E': printf("Ȳ��"); break;
			case 'S': printf("�뿹"); break;
			default: printf("�ù�"); break;
			}
			printf("\n\n* ��ǻ���� ī��\t\t: ");
			switch (comp_choice) {
			case 'E': printf("Ȳ��"); break;
			case 'S': printf("�뿹"); break;
			default: printf("�ù�"); break;
			}
			victory = compare_card(user_choice, comp_choice);
			printf("\n\n* ���: ");
			switch (victory) {
			case -1:
				printf("���� �й�"); break;
			case 0: printf("���º�"); break;
			case 1: printf("���� �¸�"); break;
			}
			printf("\n\n+++++++++++++++++++++++++++\n\n");
			if (victory == 0) {
				printf("���� �� (Enter Ű�� �Է��ϼ���...)");
				FFLUSH;
				continue;
			}
			else {
				user_score_gain = cal_score(victory, user_set);
				switch (user_score_gain) {
				case 200:
					comp_score -= 300; break;
				case 700:
					comp_score -= 500; break;
				case -500:
					comp_score += 700; break;
				case -300:
					comp_score += 200; break;
				}
				user_score += user_score_gain;

				printf("[���� ����]\n");
				printf("+++++++++++++++++++++++++++\n\n");
				printf("* ���� ����\t\t: %d\n\n", user_score);
				printf("* ��ǻ���� ����\t\t: %d\n\n", comp_score);
				printf("+++++++++++++++++++++++++++\n\n");

				if (user_score >= 2000) {
					printf("[���� ���]\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("* ����� �¸� !\n\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("Enter Ű�� �Է��ϼ���..."); FFLUSH;
					return;
				}
				else if (comp_score >= 2000) {
					printf("[���� ���]\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("* ����� �й� !\n\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("Enter Ű�� �Է��ϼ���..."); FFLUSH;
					return;
				}

				printf("������ ����Ͻðڽ��ϱ�? (y/n): ");
				scanf("%c", &replay);
				if (replay == 'y' || replay == 'Y') {
					round += 1;
					game_end = 1;
					continue;
				}
				else if (replay == 'n' || replay == 'N') {
					return;
				}
				else {
					printf("WTFFFFFF\n");
					exit(1);
				}
			}
		}
	}

}

void show_table(int round, int comp_score, int user_score,
		char user_main_card, int user_remain_citizen) {
	int i;
	int card_num = user_remain_citizen;
	if (user_main_card)
		card_num += 1;

	system("cls");
	printf("[����Ƚ��:  %d, ��ǻ��: %d��, ��: %d��]\n\n", round, comp_score, user_score);
	printf("++++++++++++++++++++++++++++++++++\n\n");
	for (i = 0; i < card_num; i++) {
		printf("������ ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("��?�� ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("������ ");
	}
	printf("\n\n");
	//printf("������ ������ ������ ������ ������ \n");
	//printf("��?�� ��?�� ��?�� ��?�� ��?�� \n");
	//printf("������ ������ ������ ������ ������ \n\n");
	for (i = 0; i < card_num; i++) {
		printf("������ ");
	}
	printf("\n");
	if (user_main_card) 
		printf("��%c�� ", user_main_card);
	for (i = 0; i < user_remain_citizen; i++) {
		printf("��C�� ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("������ ");
	}
	printf("\n\n");

	//printf( "������ ������ ������ ������ ������ \n");
	//printf("��%c�� ��C�� ��C�� ��C�� ��C�� \n", user_set);
	//printf ("������ ������ ������ ������ ������ \n\n");
	//printf("++++++++++++++++++++++++++++++++++\n\n");
}

char get_user_card(int round, int comp_score, int user_score, char user_set,
				char *user_main_card, char *user_remain_citizen) {
	int choice;
	while (1) {
		printf("[ī�� ����]\n");
		printf("++++++++++++++++\n\n");
		if (user_set == 'E')
			printf("0. Ȳ�� (1��)\n\n");
		else
			printf("0. �뿹 (1��)\n\n");
		printf("1. �ù� (1��)\n\n");
		printf("++++++++++++++++\n");
		printf("�Է�: ");
		scanf("%d", &choice); FFLUSH;
		if (choice == 0 || choice == 1) break;
		printf("�ùٸ� �޴��� �����ϼ���...\n");
		Sleep(1000);
		system("cls");
		show_table(round, comp_score, user_score, *user_main_card, *user_remain_citizen);
	}
	if (choice == 0) {
		if (*user_main_card) {
			choice = *user_main_card;
			*user_main_card = '\0';
		}
		else {
			printf("�����ϴ�. TODO\n");
		}
	}
	else {
		if (*user_main_card > 0) {
			choice = 'C';
			*user_remain_citizen -= 1;
		}
		else {
			printf("�����ϴ�. TODO\n");
		}
	}
	return choice;
}

char get_computer_card(char user_set, char *comp_main_card, char *comp_remain_citizen) {
	float choice_prob;
	char choice;

	float debug;
	
	if (*comp_main_card) {
		choice_prob = 1.0 / (*comp_remain_citizen + 1);
		// printf("%f %f", debug, choice_prob);
		if ((rand() % 1000) / 1000.0 < choice_prob) {
			choice = *comp_main_card;
			*comp_main_card = '\0';
		}
		else {
			choice = 'C';
			*comp_remain_citizen -= 1;
		}
	}

	else {
		if (*comp_remain_citizen > 0) {
			choice = 'C';
			*comp_remain_citizen -= 1;
		}
	}
	return choice;

	
}

int compare_card(user_choice, comp_choice) {
	int victory;
	
	if (user_choice == 'E') {
		if (comp_choice == 'C')
			victory = 1;
		else if (comp_choice == 'S')
			victory = -1;
	}
	else if (user_choice == 'C') {
		if (comp_choice == 'C')
			victory = 0;
		else if (comp_choice == 'S')
			victory = 1;
		else if (comp_choice == 'E')
			victory = -1;
	}
	else if (user_choice == 'S') {
		if (comp_choice == 'C')
			victory = -1;
		else if (comp_choice == 'E')
			victory = 1;
	}

	return victory;
}

int cal_score(int user_victory, char user_set) {
	if (user_set == 'E') {
		if (user_victory == 1)
			return 200;
		else
			return -500;
	}
	else {
		if (user_victory == 1)
			return 700;
		else
			return -300;
	}
}