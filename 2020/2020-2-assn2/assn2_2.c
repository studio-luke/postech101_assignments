// Started on 17:41 11/07/2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH while(getchar() != '\n');

#define N 3

void print_board(char board[][N]){
	int i, j;

	printf("\n");

	for (j = 0; j < N; j++)
		printf("+---");
	printf("+\n");

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("| %c ", board[i][j]);
		printf("|\n");
		
		for (j = 0; j < N; j++)
			printf("+---");
		printf("+\n");
	}
}

void computer_choice(char board[][N], int *h, int *w) {
	while (1) {
		*h = rand() % 3;
		*w = rand() % 3;
		if (board[*h][*w] == '*')
			break;
	}
}

// Return 'O' for O win, 'X' for X win,
// '*' for draw, '\0' for not end
char check_board(char board[][N]) {
	char marker[] = { 'O', 'X' };
	int p, i, j;
	int line;
	for (p = 0; p < 2; p++) {
		for (i = 0; i < N; i++) {

			// Horizental check
			for (j = 0; i < N; j++)
				if (board[i][j] != marker[p])
					break;
			if (j == N)
				return marker[p];

			// Vertical check
			for (j = 0; i < N; j++)
				if (board[j][i] != marker[p])
					break;
			if (j == N)
				return marker[p];
		}

		for (i = 0; i < N; i++)
			if (board[i][i] != marker[p])
				break;
		if (i == N)
			return marker[p];

		for (i = 0; i < N; i++)
			if (board[i][N - 1 - i] != marker[p])
				break;
		if (i == N)
			return marker[p];
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (board[i][j] == '*')
				return '\0';
		}
	}
	return '*';
}

int main() {
	char board[N][N];
	int result, play_again = 1;
	int i, j, turn, user_mark = 'O', comp_mark = 'X';
	int h, w;
	char buf;
	
	srand(time(NULL));

	while (play_again) {
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				board[i][j] = '*';
		turn = rand() % 2;	// 0 for user, 1 for computer
		if (turn == 1) {	// computer first
			user_mark = 'X';
			comp_mark = 'O';
		}

		while (1) {
			print_board(board);

			if (result = check_board(board))
				break;

			if (turn == 0) {
				do {
					printf("\n[User] ");
					scanf("%d%d", &h, &w);
					FFLUSH;
				} while (board[h][w] != '*');
				board[h][w] = user_mark;
			}
			else {
				computer_choice(board, &h, &w);
				board[h][w] = comp_mark;
				printf("\n[Computer] %d %d\n", h, w);
			}

			turn = !turn;
		}

		if (result == user_mark)
			printf("\nYou Win!\n");
		else if (result == comp_mark)
			printf("\nComputer Wins!\n");
		else
			printf("\nDraw!\n");

		while (1) {
			printf("Do you want to play again? (y/n) ");
			scanf("%c", &buf); FFLUSH;
			if (buf == 'y' || buf == 'Y')
				break;
			else if (buf == 'n' || buf == 'N') {
				play_again = 0;
				break;
			}
			else printf("Invalid input! ");
		}
	}
	printf("Good bye!\n");
}