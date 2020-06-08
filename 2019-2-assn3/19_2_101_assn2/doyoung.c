#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<time.h>
#include<stdlib.h>


void printMenu(void);
int checkMenu(void);
void init_board(char ary[][27]);
void view_board(char ary[][27], int score1, int score2);
void view_turn(int* turn, int menu);
int change_board(char ary[][27], int* score1, int* score2, int* turn, int* fin_coordi1, int* fin_coordi2);
void playerVsPlayer(char ary[][27]);
int AI_function(int* px, int* py, char ary[][27], int diff, int* score1, int* score2, int* count, int order);
void printDifficulty(int* diff);
void playerVsAI(char ary[][27], int diff);
void print_record(FILE* file, int x, int y);
void AIVsAI(int diff1, int diff2, char ary[][27]);

int main() {
	srand(time(NULL));
	int userPick;
	int diff, diff1, diff2;
	char board[10][27];
	while (1) {
		init_board(board);
		userPick = checkMenu();
		switch (userPick) {
		case 1:
			view_board(board, 0, 0);
			playerVsPlayer(board);
			break;

		case 2:
			printf("Which difficulty do you want?\n");
			printDifficulty(&diff);
			while (1) {
				if (diff == 1 || diff == 2 || diff == 3) {
					view_board(board, 0, 0);
					playerVsAI(board, diff);
					break;
				}
				else if (diff == 4) {
					break;
				}
				else {
					printf("Wrong value! select again\n ");
					printDifficulty(&diff);
				}
			}
			break;

		case 3:
			printf("\nWhich difficulty do you want for AI 1?\n");
			printDifficulty(&diff1);
			while (1) {
				if (diff1 == 1 || diff1 == 2 || diff1 == 3) {
					break;
				}
				else if (diff1 == 4) {
					break;
				}
				else {
					printf("Wrong value! select again\n ");
					printDifficulty(&diff1);
				}
			}
			if (diff1 == 4)
				break;
			printf("\n");
			printf("Which difficulty do you want for AI 2?\n");
			printDifficulty(&diff2);
			while (1) {
				if (diff2 == 1 || diff2 == 2 || diff2 == 3) {
					break;
				}
				else if (diff2 == 4) {
					break;
				}
				else {
					printf("Wrong value! select again\n ");
					printDifficulty(&diff2);
				}
			}
			if (diff2 == 4)
				break;
			view_board(board, 0, 0);
			AIVsAI(diff1, diff2, board);
			break;

		case 4:
			printf("Thank you for playing Dots and Boxes!");
			return 0;
		}
	}
}

void printMenu(void) {
	printf("Welcome to Dots and boxes!\n");
	printf("============================\n");
	printf("1. Game: Player vs Player\n");
	printf("2. Game: Player vs AI\n");
	printf("3. Game: AI vs AI\n");
	printf("4. Quit\n");
	printf("============================\n");
	printf("Select menu number: ");
}

int checkMenu(void) {
	int menu;
	printMenu();
	scanf("%d", &menu);
	while (menu != 1 && menu != 2 && menu != 3 && menu != 4) {
		printf("Wrong number! Select again\n");
		printMenu();
		scanf("%d", &menu);
	}
	return menu;
}

void playerVsPlayer(char ary[][27]) {
	int turn = 1;
	int valid;
	int menu = 1;
	int score1 = 0;
	int score2 = 0;
	int ini_score1, ini_score2;
	int coordi1, coordi2;
	FILE* file;
	file = fopen("PvP.txt", "w");

	while ((score1 + score2) != 16) {
		ini_score1 = score1;
		ini_score2 = score2;
		view_turn(&turn, menu);
		valid = change_board(ary, &score1, &score2, &turn, &coordi1, &coordi2);
		while (valid == 2) {
			printf("Impossible: Wrong position (Dot or box). Try again.\n");
			valid = change_board(ary, &score1, &score2, &turn, &coordi1, &coordi2);
		}
		print_record(file, coordi1, coordi2);
		if ((ini_score1 == score1) && (ini_score2 == score2))
		{
			turn++;
		}
		view_board(ary, score1, score2);
	}
	fclose(file);
	if (score1 == score2)
		printf("DRAW!");
	else if (score1 > score2)
		printf("Player 1 Wins!");
	else
		printf("Player 2 Wins!");
	printf("\n\nPress Enter key to return to the Main Menu\n");
	while (getchar() != '\n');
	while (getchar() != '\n');
}

void playerVsAI(char ary[][27], int diff) {
	int turn = 1;
	int valid;
	int menu = 2;
	int score1 = 0;
	int score2 = 0;
	int ini_score1, ini_score2;
	int coordi1, coordi2;
	int check = 2;
	int count = 1;
	FILE* file;
	file = fopen("PvA.txt", "w");
	int fin_coordi1, fin_coordi2;

	while ((score1 + score2) != 16) {
		ini_score1 = score1;
		ini_score2 = score2;
		view_turn(&turn, menu);
		if (turn % 2 != 0) {
			valid = change_board(ary, &score1, &score2, &turn, &fin_coordi1, &fin_coordi2);
			while (valid == 2) {
				printf("Impossible: Wrong position (Dot or box). Try again.\n");
				valid = change_board(ary, &score1, &score2, &turn, &fin_coordi1, &fin_coordi2);
			}
			print_record(file, fin_coordi1, fin_coordi2);
			if ((ini_score1 == score1) && (ini_score2 == score2))
			{
				turn++;
			}
			view_board(ary, score1, score2);
		}
		else {
			check = 2;
			while (check == 2) {
				coordi1 = rand() % 9;
				if (coordi1 % 2 == 0) {
					int range = 4;
					coordi2 = 2 * (rand() % range + 1) - 1;
				}
				else {
					int range = 5;
					coordi2 = 2 * (rand() % range);
				}
				check = AI_function(&coordi1, &coordi2, ary, diff, &score1, &score2, &count, 2);
			}
			print_record(file, coordi1, coordi2);
			printf("The selected position by AI is %d %d\n", coordi1, coordi2);
			if ((ini_score1 == score1) && (ini_score2 == score2))
			{
				turn++;
			}
			view_board(ary, score1, score2);
		}
	}
	fclose(file);
	if (score1 == score2)
		printf("DRAW!");
	else if (score1 > score2)
		printf("Player Wins!");
	else
		printf("AI Wins!");
	printf("\n\nPress Enter key to return to the Main Menu\n");
	while (getchar() != '\n');
	while (getchar() != '\n');
}

void AIVsAI(int diff1, int diff2, char ary[][27]) {
	int turn = 1;
	int valid;
	int menu = 3;
	int score1 = 0;
	int score2 = 0;
	int ini_score1, ini_score2;
	int coordi1, coordi2;
	int check = 2;
	int count = 1;
	FILE* file;
	file = fopen("AvA.txt", "w");
	int fin_coordi1, fin_coordi2;

	while ((score1 + score2) != 16) {
		ini_score1 = score1;
		ini_score2 = score2;
		view_turn(&turn, menu);
		if (turn % 2 != 0) {
			check = 2;
			while (check == 2) {
				coordi1 = rand() % 9;
				if (coordi1 % 2 == 0) {
					int range = 4;
					coordi2 = 2 * (rand() % range + 1) - 1;
				}
				else {
					int range = 5;
					coordi2 = 2 * (rand() % range);
				}
				check = AI_function(&coordi1, &coordi2, ary, diff1, &score1, &score2, &count, 1);
			}
			print_record(file, coordi1, coordi2);
			printf("The selected position by AI 1 is %d %d\n", coordi1, coordi2);
			if ((ini_score1 == score1) && (ini_score2 == score2))
			{
				turn++;
			}
			view_board(ary, score1, score2);
		}
		else {
			check = 2;
			while (check == 2) {
				coordi1 = rand() % 9;
				if (coordi1 % 2 == 0) {
					int range = 4;
					coordi2 = 2 * (rand() % range + 1) - 1;
				}
				else {
					int range = 5;
					coordi2 = 2 * (rand() % range);
				}
				check = AI_function(&coordi1, &coordi2, ary, diff2, &score1, &score2, &count, 2);
			}
			print_record(file, coordi1, coordi2);
			printf("The selected position by AI 2 is %d %d\n", coordi1, coordi2);
			if ((ini_score1 == score1) && (ini_score2 == score2))
			{
				turn++;
			}
			view_board(ary, score1, score2);
		}
	}
	fclose(file);
	if (score1 == score2)
		printf("DRAW!");
	else if (score1 > score2)
		printf("AI 1 Wins!");
	else
		printf("AI 2 Wins!");
	printf("\n\nPress Enter key to return to the Main Menu\n");
	while (getchar() != '\n');
	while (getchar() != '\n');
}

void init_board(char ary[][27]) {
	int i, j, k;
	for (i = 0; i < 9; i++)
	{
		ary[0][3 * i + 2] = i + 48;
		ary[i + 1][0] = i + 48;
	}
	ary[1][2] = '+';
	ary[1][8] = '+';
	ary[1][14] = '+';
	ary[1][20] = '+';
	ary[1][26] = '+';
	ary[3][2] = '+';
	ary[3][8] = '+';
	ary[3][14] = '+';
	ary[3][20] = '+';
	ary[3][26] = '+';
	ary[5][2] = '+';
	ary[5][8] = '+';
	ary[5][14] = '+';
	ary[5][20] = '+';
	ary[5][26] = '+';
	ary[7][2] = '+';
	ary[7][8] = '+';
	ary[7][14] = '+';
	ary[7][20] = '+';
	ary[7][26] = '+';
	ary[9][2] = '+';
	ary[9][8] = '+';
	ary[9][14] = '+';
	ary[9][20] = '+';
	ary[9][26] = '+';
	for (j = 0; j < 4; j++) {
		for (k = 1; k < 27; k++) {
			ary[2 * j + 2][k] = '\0';
		}
	}
	for (j = 0; j < 5; j++) {
		ary[2 * j + 1][1] = '\0';
		ary[2 * j + 1][3] = '\0';
		ary[2 * j + 1][4] = '\0';
		ary[2 * j + 1][5] = '\0';
		ary[2 * j + 1][6] = '\0';
		ary[2 * j + 1][7] = '\0';
		ary[2 * j + 1][9] = '\0';
		ary[2 * j + 1][10] = '\0';
		ary[2 * j + 1][11] = '\0';
		ary[2 * j + 1][12] = '\0';
		ary[2 * j + 1][13] = '\0';
		ary[2 * j + 1][15] = '\0';
		ary[2 * j + 1][16] = '\0';
		ary[2 * j + 1][17] = '\0';
		ary[2 * j + 1][18] = '\0';
		ary[2 * j + 1][19] = '\0';
		ary[2 * j + 1][21] = '\0';
		ary[2 * j + 1][22] = '\0';
		ary[2 * j + 1][23] = '\0';
		ary[2 * j + 1][24] = '\0';
		ary[2 * j + 1][25] = '\0';
	}
	for (i = 0; i < 27; i++) {
		if (i != 2 && i != 5 && i != 8 && i != 11 && i != 14 && i != 17 && i != 20 && i != 23 && i != 26)
			ary[0][i] = '\0';
	}
}

void view_board(char ary[][27], int score1, int score2) {
	int i, j;
	printf("\n============================\n");
	printf("     %d      vs      %d     \n", score1, score2);
	printf("============================\n");
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 27; j++) {
			printf("%c", ary[i][j]);
		}
		printf("\n");
	}
	printf("============================\n");
}

void view_turn(int* turn, int menu) {
	if (*turn % 2 == 0 && menu == 1)
		printf("Turn: Player 2\n");
	else if (*turn % 2 != 0 && menu == 1)
		printf("Turn: Player 1\n");
	else if (*turn % 2 != 0 && menu == 2)
		printf("Turn: Player \n");
	else if (*turn % 2 == 0 && menu == 2)
		printf("Turn: AI\n");
	else if (*turn % 2 == 0 && menu == 3)
		printf("Turn: AI 2 \n");
	else
		printf("Turn: AI 1\n");
}

int change_board(char ary[][27], int* score1, int* score2, int* turn, int* fin_coordi1, int* fin_coordi2) {
	int i, j;
	int coordi1, coordi2;
	int temp;
	temp = *turn;
	printf("Select the position you want to draw.\n");
	scanf("%d %d", &coordi1, &coordi2);
	*fin_coordi1 = coordi1;
	*fin_coordi2 = coordi2;
	if (temp % 2 == 0) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if (2 * i == coordi1 && (2 * j + 1) == coordi2 && (ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|'))
					{
						*score2 += 1;
						ary[2 * i][6 * j + 5] = 'X';
					}
					if ((ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|'))
					{
						*score2 += 1;
						ary[2 * i + 2][6 * j + 5] = 'X';
					}
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((i * 2 + 1) == coordi1 && 2 * j == coordi2 && (ary[i * 2 + 2][6 * j + 2] == '\0')) {
					ary[i * 2 + 2][6 * j + 2] = '|';
					if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-'))
					{
						*score2 += 1;
						ary[2 * i + 2][6 * j + 5] = 'X';
					}
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-'))
					{
						*score2 += 1;
						ary[2 * i + 2][6 * j - 1] = 'X';
					}
					return 1;
				}
			}
		}
	}
	else {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if (2 * i == coordi1 && (2 * j + 1) == coordi2 && (ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|'))
					{
						*score1 += 1;
						ary[2 * i][6 * j + 5] = 'O';
					}
					if ((ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|'))
					{
						*score1 += 1;
						ary[2 * i + 2][6 * j + 5] = 'O';
					}
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((i * 2 + 1) == coordi1 && 2 * j == coordi2 && (ary[i * 2 + 2][6 * j + 2] == '\0')) {
					ary[i * 2 + 2][6 * j + 2] = '|';
					if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-'))
					{
						*score1 += 1;
						ary[2 * i + 2][6 * j + 5] = 'O';
					}
					if ((ary[2 * i + 2][6 * j - 4] == '|' && ary[2 * i + 1][6 * j - 1] == '-' && ary[2 * i + 3][6 * j - 1] == '-'))
					{
						*score1 += 1;
						ary[2 * i + 2][6 * j - 1] = 'O';
					}
					return 1;
				}
			}
		}
	}

	return 2;
}

void printDifficulty(int* diff) {
	printf("============================\n");
	printf("1. Easy\n");
	printf("2. Normal\n");
	printf("3. Hard\n");
	printf("4. Quit\n");
	printf("============================\n");
	printf("Select menu number:");
	scanf("%d", diff);
}

int AI_function(int* px, int* py, char ary[][27], int diff, int* score1, int* score2, int* count, int order) {
	int i, j;
	if (diff == 1) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if (2 * i == *px && (2 * j + 1) == *py && (ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i][6 * j + 5] = 'X';
						}
					}
					if ((ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
					}
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((i * 2 + 1) == *px && 2 * j == *py && (ary[i * 2 + 2][6 * j + 2] == '\0')) {
					ary[i * 2 + 2][6 * j + 2] = '|';
					if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}

					}
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j - 1] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j - 1] = 'X';
						}

					}
					return 1;
				}
			}
		}
		return 2;
	}
	if (diff == 2) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i][6 * j + 5] = 'X';
					}
					*px = 2 * i;
					*py = 2 * (j + 1) - 1;
					if ((ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 3][6 * j + 5] == '-')) {
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
						return 1;
					}
					return 1;
				}

				if ((ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|' && ary[2 * i - 1][6 * j + 5] == '\0')) {
					ary[2 * i - 1][6 * j + 4] = '-';
					ary[2 * i - 1][6 * j + 5] = '-';
					ary[2 * i - 1][6 * j + 6] = '-';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i][6 * j + 5] = 'X';
					}
					*px = 2 * i - 2;
					*py = 2 * (j + 1) - 1;
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '\0')) {
					ary[2 * i + 2][6 * j + 2] = '|';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i + 2][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i + 2][6 * j + 5] = 'X';
					}
					*px = 2 * i + 1;
					*py = 2 * j;
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-')) {
						if (order == 1) {
							*score1 += 1;
						}
						else if (order == 2) {
							*score2 += 1;
						}
						return 1;
					}
					return 1;
				}
				if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-') && ary[2 * i + 2][6 * j + 2] == '\0') {
					ary[2 * i + 2][6 * j + 2] = '|';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i + 2][6 * j - 1] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i + 2][6 * j - 1] = 'X';
					}
					*px = 2 * i + 1;
					*py = 2 * j;
					return 1;
				}
			}
		}
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if (2 * i == *px && (2 * j + 1) == *py && (ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i][6 * j + 5] = 'X';
						}

					}
					if ((ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
					}
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((i * 2 + 1) == *px && 2 * j == *py && (ary[i * 2 + 2][6 * j + 2] == '\0')) {
					ary[i * 2 + 2][6 * j + 2] = '|';
					if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
					}
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j - 1] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j - 1] = 'X';
						}
					}
					return 1;
				}
			}
		}
		return 2;
	}
	else if (diff == 3) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i][6 * j + 5] = 'X';
					}
					*px = 2 * i;
					*py = 2 * (j + 1) - 1;
					if ((ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 3][6 * j + 5] == '-')) {
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
						return 1;
					}
					return 1;
				}

				if ((ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|' && ary[2 * i - 1][6 * j + 5] == '\0')) {
					ary[2 * i - 1][6 * j + 4] = '-';
					ary[2 * i - 1][6 * j + 5] = '-';
					ary[2 * i - 1][6 * j + 6] = '-';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i][6 * j + 5] = 'X';
					}
					*px = 2 * i - 2;
					*py = 2 * (j + 1) - 1;
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '\0')) {
					ary[2 * i + 2][6 * j + 2] = '|';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i + 2][6 * j + 5] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i + 2][6 * j + 5] = 'X';
					}
					*px = 2 * i + 1;
					*py = 2 * j;
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-')) {
						if (order == 1) {
							*score1 += 1;
						}
						else if (order == 2) {
							*score2 += 1;
						}
						return 1;
					}
					return 1;
				}
				if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-') && ary[2 * i + 2][6 * j + 2] == '\0') {
					ary[2 * i + 2][6 * j + 2] = '|';
					if (order == 1) {
						*score1 += 1;
						ary[2 * i + 2][6 * j - 1] = 'O';
					}
					else if (order == 2) {
						*score2 += 1;
						ary[2 * i + 2][6 * j - 1] = 'X';
					}
					*px = 2 * i + 1;
					*py = 2 * j;
					return 1;
				}
			}
		}

		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if ((ary[2 * i + 1][6 * j + 5] == '\0' && ary[2 * i + 2][6 * j + 2] == '\0' && ary[2 * i + 2][6 * j + 8] == '\0') || (ary[2 * i + 3][6 * j + 5] == '\0' && ary[2 * i + 2][6 * j + 2] == '\0' && ary[2 * i + 2][6 * j + 8] == '\0') || (ary[2 * i + 3][6 * j + 5] == '\0' && ary[2 * i + 1][6 * j + 5] == '\0' && ary[2 * i + 2][6 * j + 8] == '\0') || (ary[2 * i + 3][6 * j + 5] == '\0' && ary[2 * i + 1][6 * j + 5] == '\0' && ary[2 * i + 2][6 * j + 2] == '\0')) {
					if ((*px) % 2 == 0) {
						if (ary[*px + 1][6 * ((*py + 1) / 2) - 1] == '\0') {
							if (*px != 0 && ary[*px][6 * ((*py + 1) / 2) - 4] != '\0' && ary[*px + 1][6 * ((*py + 1) / 2) + 2] != '\0')
								return 2;
							else if (*px != 0 && ary[*px][6 * ((*py + 1) / 2) - 4] != '\0' && ary[*px - 1][6 * ((*py + 1) / 2) - 1] != '\0')
								return 2;
							else if (*px != 0 && ary[*px][6 * ((*py + 1) / 2) + 2] != '\0' && ary[*px - 1][6 * ((*py + 1) / 2) - 1] != '\0')
								return 2;
							else if (*px != 8 && ary[*px + 2][6 * ((*py + 1) / 2) - 4] != '\0' && ary[*px + 2][6 * ((*py + 1) / 2) + 2] != '\0')
								return 2;
							else if (*px != 8 && ary[*px + 2][6 * ((*py + 1) / 2) - 4] != '\0' && ary[*px + 3][6 * ((*py + 1) / 2) - 1] != '\0')
								return 2;
							else if (*px != 8 && ary[*px + 2][6 * ((*py + 1) / 2) + 2] != '\0' && ary[*px + 3][6 * ((*py + 1) / 2) - 1] != '\0')
								return 2;
						}
					}
					else if (*px % 2 != 0) {
						if (ary[*px + 1][6 * (*py / 2) + 2] == '\0') {
							if (*py != 0 && ary[*px + 1][6 * (*py / 2) - 4] != '\0' && ary[*px][6 * (*py / 2) - 1] != '\0')
								return 2;
							else if (*py != 0 && ary[*px + 1][6 * (*py / 2) - 4] != '\0' && ary[*px + 2][6 * (*py / 2) - 1] != '\0')
								return 2;
							else if (*py != 0 && ary[*px + 2][6 * (*py / 2) - 1] != '\0' && ary[*px][6 * (*py / 2) - 1] != '\0')
								return 2;
							else if (*py != 8 && ary[*px + 1][6 * (*py / 2) + 8] != '\0' && ary[*px][6 * (*py / 2) + 5] != '\0')
								return 2;
							else if (*py != 8 && ary[*px + 1][6 * (*py / 2) + 8] != '\0' && ary[*px + 2][6 * (*py / 2) + 5] != '\0')
								return 2;
							else if (*py != 8 && ary[*px + 2][6 * (*py / 2) + 5] != '\0' && ary[*px][6 * (*py / 2) + 5] != '\0')
								return 2;
						}
					}
				}
			}
		}

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 4; j++) {
				if (2 * i == *px && (2 * j + 1) == *py && (ary[2 * i + 1][6 * j + 5] == '\0')) {
					ary[2 * i + 1][6 * j + 4] = '-';
					ary[2 * i + 1][6 * j + 5] = '-';
					ary[2 * i + 1][6 * j + 6] = '-';
					if ((ary[2 * i - 1][6 * j + 5] == '-' && ary[2 * i][6 * j + 2] == '|' && ary[2 * i][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i][6 * j + 5] = 'X';
						}
					}
					if ((ary[2 * i + 3][6 * j + 5] == '-' && ary[2 * i + 2][6 * j + 2] == '|' && ary[2 * i + 2][6 * j + 8] == '|'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
					}
					return 1;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 5; j++) {
				if ((i * 2 + 1) == *px && 2 * j == *py && (ary[i * 2 + 2][6 * j + 2] == '\0')) {
					ary[i * 2 + 2][6 * j + 2] = '|';
					if ((ary[2 * i + 2][6 * j + 8] == '|' && ary[2 * i + 1][6 * j + 5] == '-' && ary[2 * i + 3][6 * j + 5] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j + 5] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j + 5] = 'X';
						}
					}
					if ((ary[2 * i + 2][6 * j - 4] == '|') && (ary[2 * i + 1][6 * j - 1] == '-') && (ary[2 * i + 3][6 * j - 1] == '-'))
					{
						if (order == 1) {
							*score1 += 1;
							ary[2 * i + 2][6 * j - 1] = 'O';
						}
						else if (order == 2) {
							*score2 += 1;
							ary[2 * i + 2][6 * j - 1] = 'X';
						}
					}
					return 1;
				}
			}
		}
		return 2;

	}
}

void print_record(FILE* file, int x, int y) {
	fprintf(file, "%d %d \n", x, y);
}