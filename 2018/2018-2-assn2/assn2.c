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
		menu = show_menu();		// 초기 메뉴 출력

		switch (menu) {
		case 1:
			print_tutorial(); break;
		case 2:
			start_game(); break;
		default:
			printf("프로그램을 종료합니다...(Press Enter)\n");
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
		printf("           1. 게임 설명\n\n");
		printf("           2. 게임 시작\n\n");
		printf("           3. 게임 종료\n\n");
		printf("++++++++++++++++++++++++++++++++++\n");
		printf("입력: ");
		scanf("%d", &command); FFLUSH;
		if (command == 1 || command == 2 || command == 3) break;
		printf("올바른 메뉴를 선택하세요...\n");
		Sleep(1000);
	}
	
	return command;
}

int print_tutorial()
{
	system("cls");
	printf("\n++++++++++++ E - Card 게임 설명 ++++++++++++\n");
	printf("\n본 게임은 도박묵시록 카이지의 E - Card 게임을 기반으로 한다.\n");
	printf("\n1. 두 플레이어는 황제패와 노예패 중 하나의 패를 각각 선택한다.\n");
	printf("황제패 = 황제 카드 1장 + 시민 카드 4장 \n");
	printf("노예패 = 노예 카드 1장 + 시민 카드 4장 \n");
	printf("\n2. 두 사용자는 매 턴마다 한 장의 카드를 안 보이게 내밀고, 함께 뒤집는다.\n");
	printf("\n3.아래의 카드 간 상성 관계에 따라 승패를 결정한다.\n");
	printf("단, 두 플레이어가 시민 카드를 냈다면, 무승부로 처리한다.\n");
	printf("\n4. 내밀었던 카드는 소모되고, 승패가 결정될 때까지 2로 돌아가 반복한다.\n");
	printf("\n상성관계: 황제 > 시민 > 노예 > 황제\n");
	printf("\n+++++++++++++++++++++++++++++++++++++++++++\n");
	printf("메뉴로 돌아가려면 Enter키를 입력하세요...");
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
			printf("[게임횟수:  %d. 컴퓨터: %d점, 나: %d점]\n\n", round, comp_score, user_score);
			printf("[카드 패 선택]\n");
			printf("++++++++++++++++++++++++++++++++++\n\n");
			printf("0. 황제패 (황제 1장, 시민 4장)\n\n");
			printf("1. 노예패 (노예 1장, 시민 4장)\n\n");
			printf("++++++++++++++++++++++++++++++++++\n");
			printf("입력: ");
			scanf("%d", &choice); FFLUSH;
			if (choice == 0 || choice == 1) break;
			printf("올바른 메뉴를 선택하세요...\n");
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

			printf("[선택 결과]\n");
			printf("+++++++++++++++++++++++++++\n\n");
			printf("* 나의 카드\t\t: ");
			switch (user_choice) {
			case 'E': printf("황제"); break;
			case 'S': printf("노예"); break;
			default: printf("시민"); break;
			}
			printf("\n\n* 컴퓨터의 카드\t\t: ");
			switch (comp_choice) {
			case 'E': printf("황제"); break;
			case 'S': printf("노예"); break;
			default: printf("시민"); break;
			}
			victory = compare_card(user_choice, comp_choice);
			printf("\n\n* 결과: ");
			switch (victory) {
			case -1:
				printf("나의 패배"); break;
			case 0: printf("무승부"); break;
			case 1: printf("나의 승리"); break;
			}
			printf("\n\n+++++++++++++++++++++++++++\n\n");
			if (victory == 0) {
				printf("다음 턴 (Enter 키를 입력하세요...)");
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

				printf("[현재 점수]\n");
				printf("+++++++++++++++++++++++++++\n\n");
				printf("* 나의 점수\t\t: %d\n\n", user_score);
				printf("* 컴퓨터의 점수\t\t: %d\n\n", comp_score);
				printf("+++++++++++++++++++++++++++\n\n");

				if (user_score >= 2000) {
					printf("[최종 결과]\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("* 당신의 승리 !\n\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("Enter 키를 입력하세요..."); FFLUSH;
					return;
				}
				else if (comp_score >= 2000) {
					printf("[최종 결과]\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("* 당신의 패배 !\n\n");
					printf("+++++++++++++++++++++++++++\n\n");
					printf("Enter 키를 입력하세요..."); FFLUSH;
					return;
				}

				printf("게임을 계속하시겠습니까? (y/n): ");
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
	printf("[게임횟수:  %d, 컴퓨터: %d점, 나: %d점]\n\n", round, comp_score, user_score);
	printf("++++++++++++++++++++++++++++++++++\n\n");
	for (i = 0; i < card_num; i++) {
		printf("┌─┐ ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("│?│ ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("└─┘ ");
	}
	printf("\n\n");
	//printf("┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ \n");
	//printf("│?│ │?│ │?│ │?│ │?│ \n");
	//printf("└─┘ └─┘ └─┘ └─┘ └─┘ \n\n");
	for (i = 0; i < card_num; i++) {
		printf("┌─┐ ");
	}
	printf("\n");
	if (user_main_card) 
		printf("│%c│ ", user_main_card);
	for (i = 0; i < user_remain_citizen; i++) {
		printf("│C│ ");
	}
	printf("\n");
	for (i = 0; i < card_num; i++) {
		printf("└─┘ ");
	}
	printf("\n\n");

	//printf( "┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ \n");
	//printf("│%c│ │C│ │C│ │C│ │C│ \n", user_set);
	//printf ("└─┘ └─┘ └─┘ └─┘ └─┘ \n\n");
	//printf("++++++++++++++++++++++++++++++++++\n\n");
}

char get_user_card(int round, int comp_score, int user_score, char user_set,
				char *user_main_card, char *user_remain_citizen) {
	int choice;
	while (1) {
		printf("[카드 선택]\n");
		printf("++++++++++++++++\n\n");
		if (user_set == 'E')
			printf("0. 황제 (1장)\n\n");
		else
			printf("0. 노예 (1장)\n\n");
		printf("1. 시민 (1장)\n\n");
		printf("++++++++++++++++\n");
		printf("입력: ");
		scanf("%d", &choice); FFLUSH;
		if (choice == 0 || choice == 1) break;
		printf("올바른 메뉴를 선택하세요...\n");
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
			printf("없습니다. TODO\n");
		}
	}
	else {
		if (*user_main_card > 0) {
			choice = 'C';
			*user_remain_citizen -= 1;
		}
		else {
			printf("없습니다. TODO\n");
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