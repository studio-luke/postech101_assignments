#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_COL 18
#define MAX_ROW 15
#define MAX_PLAYER 10
#define ORANGE "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE "\x1b[94m"
#define PURPLE "\x1b[95m"
#define RESET "\x1b[0m"


int LoadLadder(int ladder_board[][MAX_COL]);
int findway(int ladder_board[][MAX_COL], int input_num);

int main() {
	int ladder_board[MAX_ROW][MAX_COL] = { 0 };
	int input;
	LoadLadder(ladder_board);
	printf("\n>>");
	scanf("%d", &input);
	if (input == 0) {
		return 0;
	}
	else if (input == -1) {
		//1번부터 사다리타기 한 후 결과  출력 후 종료, result.txt 생성

	}

	return 0;
}

int LoadLadder(int ladder_board[][MAX_COL]) {
	int nophi, jul; //높이, 줄
	int i, j, k;
	int input, garro;
	int ladder[(MAX_PLAYER - 1) * 5][2];
	int sijak[MAX_COL];
	char dochak[MAX_COL];
	FILE *f;

	printf("start loading\n");

	f = fopen("map.txt", "r"); //파일을 읽기 모드로 연다.
	printf("open done\n");//ㅅㅈㅇㅁ
	if (f == NULL) {
		printf("Error: File not found");
		return 1;
	}
	else {
		fscanf(f, "%d %d", &input, &garro);
		for (i = 0; i < garro; i++) {
			fscanf(f, "%d %d", &ladder[i][0], &ladder[i][1]);
		}
	}
	fclose(f);


	for (i = 0; i < (input * 2 - 1); i++) {
		if (i % 2 == 0) {
			for (j = 0; j < 14; j++) {
				if (j == 0) {
					if (i == 0) {
						dochak[i] = 65;
					}
					else {
						dochak[i / 2] = 65 + i / 2;
					}
				}
				else if (j == 13) {
					if (i == 0) {
						sijak[i] = 1;
					}
					else {
						sijak[i / 2] = i / 2 + 1;
					}
				}
				else {
					ladder_board[i][j] = 1;
				}
			}
		}
		else {
			for (j = 0; j < 11; j++) {
				for (k = 0; k < garro; k++) {
					if (ladder[k][0] == j && (2 * ladder[k][1]) - 1 == i)
						ladder_board[i][j + 1] = 2;
				}
			}
		}
	}
	for (i = 0; i < input; i++) {
		printf("%c  ", dochak[i]);
	}
	printf("\n");

	for (i = 1; i < 13; i++) {
		for (j = 0; j < (input * 2 - 1); j++) {
			if (ladder_board[j][i] == 1)
				printf("+");

			else if (ladder_board[j][i] == 2)
				printf("--");

			else if (ladder_board[j][i] == 3)
				printf(ORANGE "+" RESET);
			else if (ladder_board[j][i] == 4)
				printf(GREEN "+" RESET);
			else if (ladder_board[j][i] == 5)
				printf(YELLOW "+" RESET);
			else if (ladder_board[j][i] == 6)
				printf(BLUE "+" RESET);
			else if (ladder_board[j][i] == 7)
				printf(PURPLE "+" RESET);

			else if (ladder_board[j][i] == 8)
				printf(ORANGE "--" RESET);
			else if (ladder_board[j][i] == 9)
				printf(GREEN "--" RESET);
			else if (ladder_board[j][i] == 10)
				printf(YELLOW "--" RESET);
			else if (ladder_board[j][i] == 11)
				printf(BLUE "--" RESET);
			else if (ladder_board[j][i] == 12)
				printf(PURPLE "--" RESET);

			else
				printf("  ");
		}
		printf("\n");
	}
	for (i = 0; i < input; i++) {
		printf("%d  ", sijak[i]);
	}
}

int findway(int ladder_board[][MAX_COL], int input_num)
{ //아이디어를 생각해보자.
	int x, y;
	int i;
	int arrway[100][2];

	if (input_num == 1 || input_num == 6) {
		x = 11;
		y = input_num * 2 - 2;
		ladder_board[x][y] = 3; //오랜지 색의 "+"
		arrway[0][0] = x;
		arrway[0][1] = y;

		x = 10; //처음은 무조건 위로, y는 변화없으니 생략!
		ladder_board[x][y] = 3;
		arrway[1][0] = x;
		arrway[1][1] = y;

		for (i = 0; i < 100; i++) {
			if (x != 0) { //아직 도착하지 않음
				if (ladder_board[x][y + 1] == 2) {
					ladder_board[x][y + 1] == 8; //옆으로 이동하면 -- 색깔이 바껴야 하므로
					y = y + 1;
					arrway[i + 2][0] = x;
					arrway[i + 2][1] = y;
				}
				else if (ladder_board[x][y - 1] == 2) {
					ladder_board[x][y - 1] == 8;
					y = y - 1;
					arrway[i + 2][0] = x;
					arrway[i + 2][1] = y;
				}
				else {
					ladder_board[x + 1][y] == 3; //위로 이동하면 + 색깔이 바뀐다.
					x = x + 1;
					arrway[i + 2][0] = x;
					arrway[i + 2][1] = y;
				}
			}

		}
	}
	if (input_num == 2 || input_num == 7) {
		x = 11;
		y = input_num * 2 - 2;
		ladder_board[x][y] = 4; //초록색의 "+"
		arrway[0][2] = x;
		arrway[0][3] = y;

		x = 10;
		ladder_board[x][y] = 4;
		arrway[1][2] = x;
		arrway[1][3] = y;

		for (i = 0; i < 100; i++) {
			if (x != 0) {
				if (ladder_board[x][y + 1] == 2) {
					ladder_board[x][y + 1] == 9;
					y = y + 1;
					arrway[i + 2][2] = x;
					arrway[i + 2][3] = y;
				}
				else if (ladder_board[x][y - 1] == 2) {
					ladder_board[x][y - 1] == 9;
					y = y - 1;
					arrway[i + 2][2] = x;
					arrway[i + 2][3] = y;
				}
				else {
					ladder_board[x + 1][y] == 4;
					x = x + 1;
					arrway[i + 2][2] = x;
					arrway[i + 2][3] = y;
				}
			}

		}

	}
	if (input_num == 3 || input_num == 8) {
		x = 11;
		y = input_num * 2 - 2;
		ladder_board[x][y] = 5; //노랑의 "+"
		arrway[0][4] = x;
		arrway[0][5] = y;

		x = 10; //
		ladder_board[x][y] = 5;
		arrway[1][4] = x;
		arrway[1][5] = y;

		for (i = 0; i < 100; i++) {
			if (x != 0) {
				if (ladder_board[x][y + 1] == 2) {
					ladder_board[x][y + 1] == 10; //옆으로 이동하면 -- 색깔이 바껴야 하므로
					y = y + 1;
					arrway[i + 2][4] = x;
					arrway[i + 2][5] = y;
				}
				else if (ladder_board[x][y - 1] == 2) {
					ladder_board[x][y - 1] == 10;
					y = y - 1;
					arrway[i + 2][4] = x;
					arrway[i + 2][5] = y;
				}
				else {
					ladder_board[x + 1][y] == 5; //위로 이동하면 + 색깔이 바뀐다.
					x = x + 1;
					arrway[i + 2][0] = x;
					arrway[i + 2][1] = y;
				}
			}

		}
	}
	if (input_num == 4 || input_num == 9) {
		x = 11;
		y = input_num * 2 - 2;
		ladder_board[x][y] = 6; //파랑색의 "+"
		arrway[0][6] = x;
		arrway[0][7] = y;

		x = 10; //처음은 무조건 위로, y는 변화없으니 생략!
		ladder_board[x][y] = 6;
		arrway[1][6] = x;
		arrway[1][7] = y;

		for (i = 0; i < 100; i++) {
			if (x != 0) { //아직 도착하지 않음
				if (ladder_board[x][y + 1] == 2) {
					ladder_board[x][y + 1] == 11; //옆으로 이동하면 -- 색깔이 바껴야 하므로
					y = y + 1;
					arrway[i + 2][6] = x;
					arrway[i + 2][7] = y;
				}
				else if (ladder_board[x][y - 1] == 2) {
					ladder_board[x][y - 1] == 11;
					y = y - 1;
					arrway[i + 2][6] = x;
					arrway[i + 2][7] = y;
				}
				else {
					ladder_board[x + 1][y] == 3; //위로 이동하면 + 색깔이 바뀐다.
					x = x + 1;
					arrway[i + 2][6] = x;
					arrway[i + 2][7] = y;
				}
			}

		}
	}
	if (input_num == 5 || input_num == 10) {
		x = 11;
		y = input_num * 2 - 2;
		ladder_board[x][y] = 7; //보라색의 "+"
		arrway[0][8] = x;
		arrway[0][9] = y;

		x = 10; //처음은 무조건 위로, y는 변화없으니 생략!
		ladder_board[x][y] = 7;
		arrway[1][8] = x;
		arrway[1][9] = y;

		for (i = 0; i < 100; i++) {
			if (x != 0) { //아직 도착하지 않음
				if (ladder_board[x][y + 1] == 2) {
					ladder_board[x][y + 1] == 12; //옆으로 이동하면 -- 색깔이 바껴야 하므로
					y = y + 1;
					arrway[i + 2][8] = x;
					arrway[i + 2][9] = y;
				}
				else if (ladder_board[x][y - 1] == 2) {
					ladder_board[x][y - 1] == 12;
					y = y - 1;
					arrway[i + 2][8] = x;
					arrway[i + 2][9] = y;
				}
				else {
					ladder_board[x + 1][y] == 12; //위로 이동하면 + 색깔이 바뀐다.
					x = x + 1;
					arrway[i + 2][8] = x;
					arrway[i + 2][9] = y;
				}
			}

		}
	}

	for (x = 0; x < MAX_COL; x++) {
		for (y = 0; y < input_num; y++) {
			if (ladder_board[x][y * 2 - 2] == 1 || ladder_board[x][y * 2 - 2] == 6) {
				printf(ORANGE "+" RESET);
			}
			if (ladder_board[x][y * 2 - 2] == 2 || ladder_board[x][y * 2 - 2] == 7) {
				printf(GREEN "+" RESET);
			}
			if (ladder_board[x][y * 2 - 2] == 3 || ladder_board[x][y * 2 - 2] == 8) {
				printf(YELLOW "+" RESET);
			}
			if (ladder_board[x][y * 2 - 2] == 4 || ladder_board[x][y * 2 - 2] == 9) {
				printf(BLUE "+" RESET);
			}
			if (ladder_board[x][y * 2 - 2] == 5 || ladder_board[x][y * 2 - 2] == 10) {
				printf(PURPLE "+" RESET);
			}
		}
	}
}
