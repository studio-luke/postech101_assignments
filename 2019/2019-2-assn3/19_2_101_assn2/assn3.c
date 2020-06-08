// Started at 11/10/2019 00:32 AM

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>  // ONLY WINDOWS

#define FFLUSH			while(getchar() != '\n');
#define BORDER_PRINT	printf("============================\n");
#define BOARD_H			9		// should be odd
#define BOARD_W			9		// should be odd
#define NUM_LINES		((BOARD_W/2) * (BOARD_H/2 + 1) + (BOARD_W/2 + 1) * (BOARD_H/2))
#define NUM_CELLS		((BOARD_W/2) * (BOARD_H / 2))
#define COORD			'+'

int  start_screen();
void init_board(char board[][BOARD_W]); // Fill the initial game board
void view_board(char board[][BOARD_W], int score[]); // Print the board on the console
void game(char board[][BOARD_W], int player1_type, int player2_type);
int	 choose_AI(int num);
void simple_AI_turn(char board[][BOARD_W], int level, int* px, int* py, int delay); // ONLY WINDOWS
int smart_AI_decision(char board[][BOARD_W], int x, int y);
void find_cell_wall(int x, int y, int dir, int* px, int* py);
int  play_turn(char board[][BOARD_W], int player, int type, int agent_equal, FILE* record);
int  check_cell_closed(char board[][BOARD_W], int x, int y, int player);
void print_record(FILE* record, int x, int y);

enum { False = 0, True = 1 };
enum { HUMAN = 0, EASY_AI = 1, NORM_AI = 2, HARD_AI = 3};
enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
enum { PLAYER1 = 0, PLAYER2 = 1 };

int dump[20];

int main() {
	char board[BOARD_H][BOARD_W] = { 0 };
	int ai1_type, ai2_type;
	srand(time(NULL));
	while (1) {
		init_board(board);
		switch (start_screen()) {
		case 1: game(board, HUMAN, HUMAN); break;
		case 2: 
			if (!(ai1_type = choose_AI(0))) continue;
			game(board, HUMAN, ai1_type); break;
		case 3: 
			if (!(ai1_type = choose_AI(1)) || !(ai2_type = choose_AI(2))) continue;
			game(board, ai1_type, ai2_type); break;
		default:
			printf("Thank you for playing Dots and Boxes!\n");
			return 0;
		}
	}
}

int start_screen() {
	char menu_char;
	int menu;
	while (1) {
		system("cls");	// ONLY WINDOWS
		printf("\nWelcome to Dots and boxes!\n");
		BORDER_PRINT;
		printf("1. Game: Player vs Player\n");
		printf("2. Game: Player vs AI\n");
		printf("3. Game: AI vs AI\n");
		printf("4. Quit\n");
		BORDER_PRINT;
		printf("Select menu number: ");

		scanf("%c", &menu_char); FFLUSH
			menu = menu_char - '0';
		if (1 <= menu && menu <= 4)
			return menu;
		printf("[Error] Invalid input!\n");
	}
}

// num: 0 for single AI, 1 or 2 for each of two AI agent.
int choose_AI(int num) {
	char agent_char;
	int agent;
	while (1) {
		printf("\nWhich difficulty do you want%s%c?\n", (num) ? "for AI " : "", (num) ? num + '0' : '\0');
		BORDER_PRINT;
		printf("1. Easy\n");
		printf("2. Normal\n");
		printf("3. Hard\n");
		printf("4. Quit\n");
		BORDER_PRINT;
		scanf("%c", &agent_char); FFLUSH
			agent = agent_char - '0';
		if (1 <= agent && agent <= 3)	return agent;
		else if (agent == 4)			return 0;
		printf("[Error] Invalid input!\n");
	}
}


void init_board(char board[][BOARD_W]) {
	int i, j;

	// A) Save '+' on coordinates 
	// B) Initialize element 'between A's by 0,			where player able to write line (1)
	// C) Initialize element 'surrounded by B's by ' ', where game record (O or X) is stored
	for (i = 0; i < BOARD_H; i++)
		for (j = 0; j < BOARD_W; j++)
			board[i][j] = ((i + j) % 2) ? 0 : ((i % 2) ? ' ' : COORD);
}

void view_board(char board[][BOARD_W], int score[]) {
	int i, j;
	int i_odd;

	system("cls");		// ONLY WINDOWS
	BORDER_PRINT;
	printf("      %2d      vs     %2d     \n", score[PLAYER1], score[PLAYER2]);
	BORDER_PRINT;

	// First Line
	printf(" ");
	for (j = 0; j < BOARD_W; j++) {
		printf(" %d ", j);		// Grid 
	}
	printf("\n");

	// Rest
	for (i = 0; i < BOARD_H; i++) {
		printf("%d", i);		// Grid
		i_odd = i % 2;
		for (j = 0; j < BOARD_W; j++) {
			if (i_odd) {
				if (j % 2) // j is odd
					printf(" %c ", board[i][j]);
				else
					printf(" %c ", (board[i][j]) ? '|' : ' ');
			}
			else {
				if (j % 2)  // j is odd
					printf("%s", board[i][j] ? "---" : "   ");
				else
					printf(" %c ", COORD);
			}
		}

		printf("\n");
	}
	BORDER_PRINT;
}



// return the score ther player has earned. 
int play_turn(char board[][BOARD_W], int player, int type, int agent_equal, FILE* record) {
	int x, y;
	int score_gain = 0;

	printf("Turn: %s ", type ? "AI" : "Player");
	if (agent_equal) printf("%c", player + 1 + '0');
	printf("\n");

	if (type == HUMAN) {
		while (1) {
			printf("Select the position you want to draw.\n");
			scanf("%d%d", &x, &y); FFLUSH;

			if (x == -1) exit(0);
			if (x < 0 || x >= BOARD_H || y < 0 || y >= BOARD_W)
				printf("Impossible: Out of the board.");
			else if ((x + y) % 2 == 0)
				printf("Impossible: Wrong position (Dot or box)");
			else if (board[x][y])
				printf("Impossible: Already drawn");
			else {
				board[x][y] = 1;
				break;
			}

			printf(" Try again.\n");
		}
	}
	else {
		simple_AI_turn(board, type, &x, &y, agent_equal ? 500 : 1000);	// ONLY WINDOWS
	}

	if (x % 2) {  // x is odd, player has drawn vertical line
		if (y < BOARD_W - 1)	score_gain += count_cell_walls(board, x, y + 1, dump, player) / 4;
		if (y > 0)				score_gain += count_cell_walls(board, x, y - 1, dump, player) / 4;

	}
	else { // player has drawn horizontal line
		if (x < BOARD_H - 1)	score_gain += count_cell_walls(board, x + 1, y, dump, player) / 4;
		if (x > 0)				score_gain += count_cell_walls(board, x - 1, y, dump, player) / 4;
	}

	print_record(record, x, y);
	return score_gain;
}

void simple_AI_turn(char board[][BOARD_W], int level, int* px, int* py, int delay) { // ONLY WINDOWS
	int i, j, dir, cnt = 0, rnd_select;
	int empty[2][NUM_LINES];
	int unclosed[4];

	enum { x = 0, y = 1 };

	Sleep(delay);	// ONLY WINDOWS
	
	if (level >= NORM_AI) 
		// Check each cells which is able to complete.
		for (i = 1; i < BOARD_H; i += 2) 
			for (j = 1; j < BOARD_W; j += 2) {
				
				if (count_cell_walls(board, i, j, unclosed, -1) == 3) {
					for (dir = 0; dir < 4; dir++)
						if (unclosed[dir]) {
							find_cell_wall(i, j, dir, &empty[x][cnt], &empty[y][cnt]);
							cnt++; break;
						} 
				}
				// cnt += check_cell_almost_closed(board, i, j, &empty[x][cnt], &empty[y][cnt]);
			}

	while (cnt == 0) {
		
		for (i = 0; i < BOARD_H; i++)
			for (j = 0; j < BOARD_W; j++) {
				if (board[i][j] == 0) {
					if (level == HARD_AI && smart_AI_decision(board, i, j))
						continue;
					empty[x][cnt] = i;
					empty[y][cnt++] = j;
				}
			}
		level = EASY_AI;
		/*HARD AI*/
		if (0) {
			int visited[2][NUM_CELLS];
			int unclosed[4], num_uncl;
			int i, j, dir, flag = 0;
			int x1, y1, x2, y2;
			for (i = 1; i < BOARD_H; i += 2)
				for (j = 1; j < BOARD_W; j += 2) {
					if (visited[x][i / 2] && visited[y][j / 2]) continue;
					else {
						visited[x][i / 2] = visited[y][j / 2] = 1;
					}
					switch (count_cell_walls(board, i, j, unclosed, -1)) {
					case 2:
						if (i == 1 || i == BOARD_H - 2 || j == 1 || j == BOARD_W - 2)
							for (dir = 0; dir < 4; dir++)
								if (unclosed[dir]) {
									find_cell_wall(i, j, dir, &x1, &y1);
									if (0 < x1 && x1 < BOARD_H - 1 && 0 < y1 && y1 < BOARD_W - 1) {
										
									}
									if (flag)
										find_cell_wall(i, j, dir, &x2, &y2);
									else {
										find_cell_wall(i, j, dir, &x1, &y1);
										flag = 1;
									}
								}

					}

				}
		}
	}
	rnd_select = rand() % cnt;
	*px = empty[x][rnd_select];
	*py = empty[y][rnd_select];
	board[*px][*py] = 1;

}

int smart_AI_decision(char board[][BOARD_W], int x, int y) {
	int i, j;
	int dangerous = 0;

	board[x][y] = 1;
	if (x % 2) {  // x is odd, player has drawn vertical line
		if (y < BOARD_W - 1)	dangerous |= count_cell_walls(board, x, y + 1, dump, -1) == 3;
		if (y > 0)				dangerous |= count_cell_walls(board, x, y - 1, dump, -1) == 3;

	}
	else { // player has drawn horizontal line
		if (x < BOARD_H - 1)	dangerous |= count_cell_walls(board, x + 1, y, dump, -1) == 3;
		if (x > 0)				dangerous |= count_cell_walls(board, x - 1, y, dump, -1) == 3;
	}
	board[x][y] = 0;

	return dangerous;
}

int count_cell_walls(char board[][BOARD_W], int x, int y, int unclosed[4], int player) {
	int count = 0, i;

	unclosed[UP] = !board[x - 1][y];
	unclosed[DOWN] = !board[x + 1][y];
	unclosed[LEFT] = !board[x][y - 1];
	unclosed[RIGHT] = !board[x][y + 1];

	for (i = 0; i < 4; i++) count += !unclosed[i];
	
	if (player != -1 && count == 4) board[x][y] = (player) ? 'X' : 'O';

	return count;
}

void find_cell_wall(int x, int y, int dir, int *px, int *py) {
	switch (dir) {
	case UP:	*px = x - 1;  *py = y;		break;
	case DOWN:	*px = x + 1;  *py = y;		break;
	case LEFT:	*px = x;	  *py = y - 1;	break;
	case RIGHT: *px = x;	  *py = y + 1;	break;
	}
}

void game(char board[][BOARD_W], int p1_type, int p2_type) {
	int score[2] = { 0, 0 }, score_gain;
	int type[2] = { p1_type, p2_type };
	int turn = 0, line = 0, player;
	int max_score = NUM_CELLS;
	int agent_equal = !((p1_type > 0) ^ (p2_type > 0));
	int winner;
	FILE* record = fopen(p1_type ? "AvA.txt" : (p2_type ? "PvA.txt" : "PvP.txt"), "w");

	while (score[0] + score[1] < max_score) {
		player = turn % 2;
		view_board(board, score);
		score_gain = play_turn(board, player, type[player], agent_equal, record);

		score[player] += score_gain;
		if (score_gain == 0) turn++; // Next player's turn
	}

	/* Print Result */
	view_board(board, score);
	if (score[PLAYER1] == score[PLAYER2])
		printf("DRAW!\n\n");
	else {
		winner = (score[PLAYER1] > score[PLAYER2]) ? PLAYER1 : PLAYER2;
		printf("%s", type[winner] ? "AI" : "Player");
		if (agent_equal) printf(" %c", winner + 1 + '0');
		printf(" Wins!!\n\n");

	}
	fclose(record);

	printf("Press Enter key to return to the Main Menu.");
	FFLUSH;
}

void print_record(FILE* record, int x, int y) {
	fprintf(record, "%d %d\n", x, y);
}