// Started at 23:03 06/09/2020
// Code by Studio Luke

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <conio.h>

#define FFLUSH	while(getchar() != '\n');

enum color { GREEN = 10, SKYBLUE = 11, YELLOW = 14, WHITE = 7 };
enum cell { P1 = 0, P2 = 1, EMPTY, DUPABLE, MOVABLE, SELECTED };
enum gameStatus { CONTINUE = 0, P1WIN, P2WIN, DRAW };
enum tryAgain {NO, YES};

typedef struct {
	int r;
	int c;
} Point;

typedef struct {
	int row;
	int col;
	enum cell** map;

	enum cell curpl; // current player
	Point cursor[2];
	Point selected; // (-1, -1) if not selected
	
	int score[2];
} Board;


int generate_map(Board* b) {
	int row, col;

	system("cls");
	printf("[ATAXX]\n");
	while (1) {
		printf("row: "); scanf("%d", &row); FFLUSH;
		if (row < 4 || 20 < row) {
			printf("Please Enter a number between 4 ~ 20\n\n");
			continue;
		} break;
	}
	while (1) {
		printf("col: "); scanf("%d", &col); FFLUSH;
		if (col < 4 || 20 < col) {
			printf("Please Enter a number between 4 ~ 20\n\n");
			continue;
		} break;
	}
	
	// Map Allocation
	b->row = row;
	b->col = col;
	b->map = (enum cell**)malloc(row * sizeof(enum cell*));
	for (int i = 0; i < row; i++)
		b->map[i] = (enum cell*)malloc(col * sizeof(enum cell));
	
	for (int r = 0; r < row; r++)
		for (int c = 0; c < col; c++)
			b->map[r][c] = EMPTY;

	// Initiate Position
	b->map[0][0] = b->map[0][col - 1] = P1;
	b->map[row - 1][0] = b->map[row - 1][col - 1] = P2;

	// Initiate Player
	b->curpl = P1;

	// Initiate Cursor Position
	b->cursor[P1].r = 0;
	b->cursor[P1].c = 0;
	b->cursor[P2].r = row - 1;
	b->cursor[P2].c = col - 1;
	b->selected.r = b->selected.c = -1;

	// Initiate Score
	b->score[P1] = b->score[P2] = 2;
}

void print_germ(enum cell gtype) {
	enum color c;
	if (gtype == P1)			c = YELLOW;
	else if (gtype == P2)		c = GREEN;
	else if (gtype == SELECTED)	c = SKYBLUE;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("@");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

int print_map(Board b) {
	int r, c;
	int is_cursor;

	printf("[Player 1] %d : %d [Player 2]\n\n", b.score[P1], b.score[P2]);
	printf("Player ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), b.curpl == P1 ? YELLOW : GREEN);
	printf("%d", b.curpl + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	printf("'s Turn\n");
	
	// Print Board
	for (r = 0; r < b.row; r++)
	{
		for (c = 0; c < b.col; c++)
			printf("+---");
		printf("+\n"); // print border

		for (c = 0; c < b.col; c++) {
			is_cursor = r == b.cursor[b.curpl].r && c == b.cursor[b.curpl].c;
			printf("|");
			printf("%c", is_cursor ? '[' : ' ');
			if(b.map[r][c] == EMPTY) printf(" ");
			else if (b.map[r][c] == DUPABLE) printf("+");
			else if (b.map[r][c] == MOVABLE) printf("x");
			else print_germ(b.map[r][c]);
			printf("%c", is_cursor ? ']' : ' ');
		}
		printf("|\n"); // print cell line
	}

	for (c = 0; c < b.col; c++)
		printf("+---");
	printf("+\n"); // print border
	printf(" - i,j,k,l: move cursor\n");
	printf(" - space: select or move\n\n");
}

int is_selected(Board b) {
	return b.selected.r != -1 && b.selected.c != -1;
}

int deselect_germ(Board *b) {
	Point* selected = &b->selected;

	if (b->map[selected->r][selected->c] != EMPTY)
		b->map[selected->r][selected->c] = b->curpl;
	for (int r = max(selected->r - 2, 0);
			r <= min(selected->r + 2, b->row - 1); r++)
		for (int c = max(selected->c - 2, 0);
				c <= min(selected->c + 2, b->col - 1); c++)
			if (b->map[r][c] == DUPABLE || b->map[r][c] == MOVABLE)
				b->map[r][c] = EMPTY;

	selected->r = selected->c = -1;
}

int select_germ(Board *b) {
	Point* selected = &b->selected;
	Point* cursor = &b->cursor[b->curpl];
	if (is_selected(*b))
		deselect_germ(b);

	if (b->map[cursor->r][cursor->c] == b->curpl) {
		b->map[cursor->r][cursor->c] = SELECTED;
		selected->r = cursor->r;
		selected->c = cursor->c;

		for (int r = max(selected->r - 2, 0);
				 r <= min(selected->r + 2, b->row - 1); r++)
			for (int c = max(selected->c - 2, 0); 
					 c <= min(selected->c + 2, b->col - 1); c++)
				if (b->map[r][c] == EMPTY) {
					if (abs(r - selected->r) == 2 || abs(c - selected->c) == 2) 
						b->map[r][c] = MOVABLE;
					else b->map[r][c] = DUPABLE;
				}
	}
}

void infect_near_cursor(Board *b) {
	Point* cursor = &b->cursor[b->curpl];

	for (int r = max(cursor->r - 1, 0);
			r <= min(cursor->r + 1, b->row - 1); r++)
		for (int c = max(cursor->c - 1, 0);
				c <= min(cursor->c + 1, b->col - 1); c++)
			if (b->map[r][c] == !b->curpl) {
				b->map[r][c] = b->curpl;
				b->score[b->curpl] += 1;
				b->score[!b->curpl] -= 1;
			}

}

char lower(char c) {
	if ('A' <= c && c <= 'Z')
		c = c - 'A' + 'a';
}

enum tryAgain try_again() {
	char regame;

	while (1) {
		printf("Continue? (y/n) ");
		scanf("%c", &regame); FFLUSH;
		regame = lower(regame);
		if (regame == 'y')
			return YES;
		else if (regame == 'n')
			return NO;
		else {
			printf("Wrong choice!\n\n");
			continue;
		}
	}
}

// Return Winner if exists.
enum gameStatus is_end(Board b) {
	char regame;
	
	if (b.score[P1] == 0)
		return P2WIN;
	else if (b.score[P2] == 0)
		return P1WIN;
	else if (b.score[P1] + b.score[P2] == b.row * b.col) {
		if (b.score[P1] == b.score[P2]) return DRAW;
		else return (b.score[P1] > b.score[P2] ? P1WIN : P2WIN);
	}
	else return CONTINUE;
}

void change_player(Board* b) {
	int r, c, dr, dc;

	// If counterplayer has no choice to move on, shouldn't change turn
	for (r = 0; r < b->row; r++)
		for (c = 0; c < b->col; c++) {
			if (b->map[r][c] == !b->curpl) {
				// Found counterplayer's cell !
				for (dr = max(r - 2, 0);
					dr <= min(r + 2, b->row - 1); dr++) {
					for (dc = max(c - 2, 0);
						dc <= min(c + 2, b->col - 1); dc++) {
						if (b->map[dr][dc] == EMPTY) {
							// There's movable space! Player can be changed
							if (!is_end(*b))
								b->curpl = !b->curpl;
							return;
						}
					}
				}
			}
		}
}


enum gameState game(Board b) {
	char cmd, winner;
	Point* cursor;

	while (1) {
		system("cls");
		print_map(b);

		if (winner = is_end(b)) {
			if (winner == DRAW)	printf("DRAW!\n");
			else printf("Player %d wins\n", winner);
			return try_again();
		}
			
		cursor = &b.cursor[b.curpl];
		cmd = lower(_getch());
		switch (cmd) {
		case 'i':  // move cursor up
			if (cursor->r > 0)
				cursor->r -= 1;
			break;
		case 'j': // move cursor left
			if (cursor->c > 0)
				cursor->c -= 1;
			break;
		case 'k': // move cursor down
			if (cursor->r < b.row - 1)
				cursor->r += 1;
			break;
		case 'l':
			if (cursor->c < b.col - 1)
				cursor->c += 1;
			break;
		case ' ':
			if (b.map[cursor->r][cursor->c] == b.curpl) 
				select_germ(&b);
			else if (b.map[cursor->r][cursor->c] == DUPABLE) {
				b.map[cursor->r][cursor->c] = b.curpl;
				b.score[b.curpl] += 1;
				deselect_germ(&b);
				infect_near_cursor(&b);
				change_player(&b);
			}
			else if (b.map[cursor->r][cursor->c] == MOVABLE) {
				b.map[cursor->r][cursor->c] = b.curpl;
				b.map[b.selected.r][b.selected.c] = EMPTY;
				deselect_germ(&b);
				infect_near_cursor(&b);
				change_player(&b);
			}
		}
	}
}

int main() {
	Board board;
	enum gameStatus regame;

	while (1) {
		generate_map(&board);
		
		// Play Game
		regame = game(board);

		// Game is Finished. Free Allocation
		for (int i = 0; i < board.row; i++)
			free(board.map[i]);
		free(board.map);

		if (regame == NO) break;
	}

	printf("Press Enter to quit..."); FFLUSH;
	return 0;
}