#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH			while(getchar() != '\n')
#define MAX_PLAYER		10
#define LADDER_HEIGHT	12

#define MAX_ROW			((MAX_PLAYER - 1) * 2 + 1)
#define MAX_COL			(LADDER_HEIGHT + 2)

#define COL1	"\x1b[91m"
#define COL2	"\x1b[92m"
#define COL3	"\x1b[93m"
#define COL4	"\x1b[94m"
#define COL5	"\x1b[95m"
#define RESET	"\x1b[0m"

int assn3_1();
int assn3_2();
void GenerateLadder(int num_player, int num_hline, int ladder[][2]);
int SaveLadder(int num_player, int num_hline, int ladder[][2]);
int LoadLadder(char ladder_board[][MAX_ROW],
	int* num_player, int* num_hline, int* map_x, int* map_y);

int main()
{
	char command;
	int code;
	srand(time(NULL));

	code = assn3_1();
	if (code != 0) return code;
	while (1) {
		printf("사다리를 출력하시겠습니까? (y/n) : ");
		scanf("%c", &command); FFLUSH;
			if (command == 'y' || command == 'Y')
				break;
			else if (command == 'n' || command == 'N')
				return 0;
			else {
				printf("입력값이 잘못되었습니다.");
				continue;
			}
	}
	system("cls");
	code = assn3_2();
	return code;
}

//	===========================================================
//	              THIS IS THE START OF ASSN3_1
//	===========================================================

int assn3_1()
{
	int num_player, num_hline;
	int ladder[46][2];
	// srand(time(NULL));
	printf("참여인원수(2 ~ 10): ");
	scanf("%d", &num_player); FFLUSH;
		if (num_player < 2 || num_player > MAX_PLAYER) {
			printf("입력값이 잘못되었습니다.\n");
			printf("Press Enter..."); FFLUSH;
			return 1;
		}

	printf("가로줄 개수(0 ~ : %d): ",
		(num_player - 1) * (LADDER_HEIGHT / 2 - 1));
	scanf("%d", &num_hline); FFLUSH;
		if (num_hline < 0 ||
			num_hline > (num_player - 1) * (LADDER_HEIGHT / 2 - 1)) {
			printf("입력값이 잘못되었습니다.\n");
			printf("Press Enter..."); FFLUSH;
			return 1;
		}

	GenerateLadder(num_player, num_hline, ladder);
	if (SaveLadder(num_player, num_hline, ladder))
		printf("사다리가 생성되었습니다. txt 파일을 확인하십시오.\n");
	else {
		printf("프로그램을 종료합니다.\n");
		printf("Press Enter..."); FFLUSH;
		return 2;
	}
	return 0;
}

void GenerateLadder(int num_player, int num_hline, int ladder[][2]) {
	int i = 0;
	int chk_valid_lad[LADDER_HEIGHT - 2][MAX_PLAYER] = { 0 };
		// This array is for checking in the process of building
		// if a h-line is adjacent to another h-line.
	int cand_x, cand_y;
	enum existence { no, yes };

	while (1) {
		cand_x = rand() % (num_player - 1);
		cand_y = rand() % (LADDER_HEIGHT - 2);
		
		// Check if it is valid position
		if (cand_x < num_player - 1)
			if (chk_valid_lad[cand_y][cand_x + 1] == yes)
				continue;
		if (cand_x > 0)
			if (chk_valid_lad[cand_y][cand_x - 1] == yes)
				continue;
		if (chk_valid_lad[cand_y][cand_x] == yes)
			continue;

		chk_valid_lad[cand_y][cand_x] = yes;
		ladder[i][0] = cand_y + 1;
		ladder[i][1] = cand_x + 1;
		if (++i >= num_hline) break;
	}
}

int SaveLadder(int num_player, int num_hline, int ladder[][2]) {
	FILE* fp = fopen("map.txt", "w");
	int i;

	if (fp == NULL) {
		printf("FATAL ERROR: Cannot Open Save File!\n");
		return 0;
	}

	fprintf(fp, "%d %d\n", num_player, num_hline);
	for (i = 0; i < num_hline; i++) {
		fprintf(fp, "%d %d\n", ladder[i][0], ladder[i][1]);
	}

	fclose(fp);
	return 1;
}

//	===========================================================
//	              THIS IS THE START OF ASSN3_2
//	===========================================================

int assn3_2()
{

	int num_player, num_hline;
	char ladder_board[MAX_COL][MAX_ROW];
	int map_x, map_y;
	int i, j, player;
	int cur_x, cur_y;
	int color[MAX_COL][MAX_ROW];
	int num_to_print;
	int color_picker;

	for (i = 0; i < MAX_COL; i++)
		for (j = 0; j < MAX_ROW; j++) {
			ladder_board[i][j] = ' ';
			color[i][j] = 0;
		}

	if (!LoadLadder(ladder_board, &num_player,
		&num_hline, &map_x, &map_y)) {
		printf("프로그램을 종료합니다.\n");
		printf("Press Enter..."); FFLUSH;
		return 2;
	}
	while(1) {
		printf("숫자를 입력하세요!\n");
		printf("1 ~ %d:\t당첨 결과 보기\n", num_player);
		printf("    0:\t종료\n");
		printf("   -1:\t전체 결과 보기 및 종료\n");
		while (1) {
			printf(">> ");
			scanf("%d", &num_to_print); FFLUSH;
			if (num_to_print < -1 || num_to_print > num_player)
				printf("Invalid Input!\n");
			else break;
		}

		if (num_to_print == 0)
			return 0;
		else if (num_to_print == -1) {
			for (player = 1; player <= num_player; player++) {
				cur_x = (player - 1) * 2;
				cur_y = map_y - 2;
				while (cur_y > 0) {
					if (cur_x > 0 && ladder_board[cur_y][cur_x - 1] == '-')
						cur_x -= 2;
					else if (cur_x < map_x - 1 && ladder_board[cur_y][cur_x + 1] == '-')
						cur_x += 2;
					cur_y -= 1;
				}
				printf("%d -> %c\n", player, ladder_board[cur_y][cur_x]);
			}
			printf("Press Enter..."); FFLUSH;
			return 0;
		}

		cur_x = (num_to_print - 1) * 2;
		cur_y = map_y - 2;
		color_picker = (num_to_print - 1) % 5 + 1;

		for (i = 0; i < map_y; i++)
			for (j = 0; j < map_x; j++)
				if (color[i][j] == color_picker)
					color[i][j] = 0;

		color[cur_y][cur_x] = color_picker;
		while (1) {
			system("cls");
			printf("X: %2d, Y: %2d\n", cur_x, cur_y - 1);
			for (i = 0; i < map_y; i++) {
				for (j = 0; j < map_x; j++) {
					if (color[i][j] == 1)
						printf(COL1);
					else if (color[i][j] == 2)
						printf(COL2);
					else if (color[i][j] == 3)
						printf(COL3);
					else if (color[i][j] == 4)
						printf(COL4);
					else if (color[i][j] == 5)
						printf(COL5);
					
					if (ladder_board[i][j] == '-' || ladder_board[i][j] == ' ')
						printf("%c", ladder_board[i][j]);
					printf("%c", ladder_board[i][j]);
					printf(RESET);
				}
				printf("\n");
			}
			if (ladder_board[cur_y][cur_x] == '+') {
				if (cur_x > 0 && ladder_board[cur_y][cur_x - 1] == '-'
					&& color[cur_y][cur_x - 1] != color_picker) {
					color[cur_y][--cur_x] = color_picker;
				}
				else if (cur_x < map_x - 1 && ladder_board[cur_y][cur_x + 1] == '-'
					&& color[cur_y][cur_x + 1] != color_picker) {
					color[cur_y][++cur_x] = color_picker;
				}
				else 
					color[--cur_y][cur_x] = color_picker;
			}
			else if (ladder_board[cur_y][cur_x] == '-') {
				if (color[cur_y][cur_x - 1] != color_picker)
					color[cur_y][--cur_x] = color_picker;
				else if (color[cur_y][cur_x + 1] != color_picker)
					color[cur_y][++cur_x] = color_picker;
			}
			if (cur_y <= 0)
				break;
			printf("Press Enter..."); FFLUSH;
		}
		printf("================================\n");
		printf("result: %d -> %c\n", num_to_print, ladder_board[cur_y][cur_x]);
		printf("================================\n\n");
	}
	return 0;
}

int LoadLadder(char ladder_board[][MAX_ROW],
	int* num_player, int* num_hline, int* map_x, int* map_y)
{
	FILE* fp = fopen("map.txt", "r");
	int i, j, tmp_x, tmp_y;

	// Open File
	if (fp == NULL) {
		printf("Cannot Read Map File");
		return 0;
	}
	fscanf(fp, "%d %d", num_player, num_hline);
	*map_x = (*num_player - 1) * 2 + 1;	// Do Not Change It...
	*map_y = MAX_COL;					// Do Not Change It...

	for (i = 0; i < *map_y; i++)
		for (j = 0; j < *map_x; j = j + 2) {
			if (i == 0)
				ladder_board[i][j] = 'A' + j / 2;
			else if (i == *map_y - 1) {
				ladder_board[i][j] = '1' + j / 2;
				if (j / 2 >= 9)
					ladder_board[i][j] = '0';
			}
			else
				ladder_board[i][j] = '+';
		}

	for (i = 0; i < *num_hline; i++) {
		fscanf(fp, "%d %d", &tmp_y, &tmp_x);
		ladder_board[tmp_y + 1][(tmp_x - 1) * 2 + 1] = '-';
	}
	fclose(fp);

	printf("\n");
	for (i = 0; i < *map_y; i++) {
		for (j = 0; j < *map_x; j++) {
			if (ladder_board[i][j] == '-' || ladder_board[i][j] == ' ')
				printf("%c", ladder_board[i][j]);
			printf("%c", ladder_board[i][j]);
		}
		printf("\n");
	}

	return 1;
}