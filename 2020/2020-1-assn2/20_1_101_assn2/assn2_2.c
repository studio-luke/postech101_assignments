/*  Started  at 02:36 AM 5/23/2020
 *  Finished at 
 *  Code by Studio Luke
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define BOARD_W		4
#define BOARD_H		4

#define FFLUSH		while(getchar() != '\n')

void init_board(int board[][BOARD_W], int play_board[][BOARD_W]) {
	int done[BOARD_H * BOARD_W] = { 0 };
	int rand_idx, value = 1;

	for (int i = 0; i < BOARD_H; i++)
		for (int j = 0; j < BOARD_W; j++)
			play_board[i][j] = 0;

	while (value <= 16) {
		do {
			rand_idx = rand() % (BOARD_H * BOARD_W);
		} while (done[rand_idx]);

		done[rand_idx] = 1;
		board[rand_idx / 4][rand_idx % 4] = ++value / 2;
	}

	return;
}

void print_board(int board[][BOARD_W]) {
	int i, j;

	printf("\n   ");
	for (i = 0; i < BOARD_W; i++)	printf("  %d ", i);
	printf("\n   +");
	for (i = 0; i < BOARD_W; i++) printf("---+");
	printf("\n");
	
	for (i = 0; i < BOARD_H; i++) {
		printf(" %d |", i);
		for (j = 0; j < BOARD_W; j++) {
			if (board[i][j])	printf(" %d |", board[i][j]);
			else				printf(" * |");
		}
		printf("\n   +");
		for (j = 0; j < BOARD_W; j++) printf("---+");
		printf("\n");
	}
}

int main() {
	int turn;
	int ans_board[BOARD_H][BOARD_W];
	int play_board[BOARD_H][BOARD_W] = { 0 };
	int h1, w1, h2, w2, is_correct;
	int p1score, p2score;
	char cont;

	srand(time(NULL));
	while (1) {			// Start of the game
		init_board(ans_board, play_board);
		p1score = p2score = 0;
		printf("Memorize the board number!!\n");
		print_board(ans_board);
		Sleep(3000);
		system("cls");

		print_board(play_board);
		turn = rand() % 2;
		while (1) {
			printf("\n[player %d] : ", turn + 1);
			scanf("%d%d%d%d", &h1, &w1, &h2, &w2); FFLUSH;
			if (play_board[h1][w1] || play_board[h2][w2]) {
				printf("\nalready open... try again..\n");
				continue;
			}
			play_board[h1][w1] = ans_board[h1][w1];
			play_board[h2][w2] = ans_board[h2][w2];
			print_board(play_board);
			is_correct = play_board[h1][w1] == play_board[h2][w2];

			if (is_correct) {
				printf("\nplayer %d get score!!\n", turn + 1);
				if (turn == 0)	p1score += 1;
				else			p2score += 1;
				printf("---------------------------\n");
				printf("[player 1] %d : %d [player 2]\n", p1score, p2score);
				printf("---------------------------\n\n");
				if (p1score + p2score < 8) {
					printf("player %d get one more chance!!\n", turn + 1);
					continue;
				}
				else {
					if (p1score == p2score) printf("Game End! Draw!\n");
					else printf("Game End! Player %d wins!\n", (p1score > p2score) ? 1 : 2);
					printf("Continue? (y/n) ");
					scanf("%c", &cont); FFLUSH;
					if (cont == 'y' || cont == 'Y') {
						printf("\n New Game!\n");
						break;
					}
					else if (cont == 'n' || cont == 'N') {
						printf("Good bye\n");
						return 0;
					}
				}
			}
			else {
				printf("\nMismatch!\n");
				Sleep(3000);
				play_board[h1][w1] = play_board[h2][w2] = 0;
				system("cls");
				print_board(play_board);
				turn = !turn;
			}
		}
	}
}