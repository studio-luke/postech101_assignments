#include <stdio.h>

#define BOARD_H			9		// should be odd
#define BOARD_W			9		// should be odd

// return 1 if the player gets score.
int check_cell_closed(char board[][BOARD_W], int x, int y, int player) {
	if ((x + y) % 2 == 0 && board[x + 1][y] && board[x - 1][y] &&
		board[x][y + 1] && board[x][y - 1]) {
		board[x][y] = (player) ? 'X' : 'O';
		return 1;
	}
	return 0;
}

int check_cell_almost_closed(char board[][BOARD_W], int x, int y, int* px, int* py) {
	int tmpx, tmpy;
	if (board[x - 1][y] + board[x + 1][y] + board[x][y - 1] + board[x][y + 1] == 3) {
		board[tmpx = x - 1][tmpy = y] && board[tmpx = x + 1][tmpy = y] &&
			board[tmpx = x][tmpy = y - 1] && board[tmpx = x][tmpy = y + 1];
		*px = tmpx;
		*py = tmpy;
		return 1;
	}
	return 0;
}