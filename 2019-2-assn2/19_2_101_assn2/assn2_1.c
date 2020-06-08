// Started at 03:08, 10/13/2019 Sun.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning (disable : 4996)

#define FFLUSH		while(getchar() != '\n')
#define RAND_START	1
#define RAND_END	5
#define BALL_MAX	15

int getResponse();
int getRandomBalls(int start, int end);
int changeBallStatus(int current, int plus);
void broadcast(int p1_black, int p2_black, int turn);
void printCurrentBallStatus(int num);
int movePlayer1(int player1, int player2);
int movePlayer2(int player1, int player2);
int isResponseValid(int response, int prevResponse);
int calcWinner(int player1, int player2);
int printWinner(int player1, int player2);

int main() {
	int chance = 3;
	int game_choice;
	int p1_get_black, p2_get_black;
	int p1_playing = 1, p2_playing = 1;
	int p1_white = 15, p1_black = 0;
	int p2_white = 15, p2_black = 0;

	srand(time(NULL));
	
	broadcast(0, 0, -1); // Show Initial State
	while (1) {
		if (chance <= 0 || !(p1_playing || p2_playing))
			break;

		game_choice = getResponse();
		if (!isResponseValid(game_choice, p1_playing + 2 * p2_playing)) {
			printf("%d IS NOT VALID RESPONSE", game_choice);
			return 1;
		}
		if		(game_choice == -1)	p1_playing = 0;
		else if (game_choice == -2) p2_playing = 0;

		if (p1_playing) p1_black = movePlayer1(p1_black, p2_black);
		if (p2_playing) p2_black = movePlayer2(p1_black, p2_black);
		if (p1_playing ^ p2_playing) chance--;
	}
	printWinner(p1_black, p2_black);
	
	return 0;
}

int getResponse() {
	int input;

	printf("\nPROCEED OR NOT? ENTER ANSWER WITH [GO 3, END -PLAYER NUM(-1 OR -2)] ");
	scanf("%d", &input); FFLUSH;

	return input;

} // Get input from player

int getRandomBalls(int start, int end) {
	int interval = end - start;
	return rand() % interval + start;
} // Give random # of black balls to player

int changeBallStatus(int current, int plus) {
	return (current + plus) % 15;
} // update the # of black balls of a player

void broadcast(int p1_black, int p2_black, int turn) {
	
	if (turn != -1) printf("\nAFTER P%d\n", turn);
	
	printf("P1 ");
	printCurrentBallStatus(p1_black);
	printf("\n");

	printf("P2 ");
	printCurrentBallStatus(p2_black);
	printf("\n");
}

void printCurrentBallStatus(int num) {
	int i;
	for (i = 0; i < num; i++)		printf("¡Ü");
	for (i = 0; i < 15 - num; i++)	printf("¡Û");
} // print current state of balls
  // num : # of black balls


int movePlayer1(int player1, int player2) {
	int get_black = getRandomBalls(RAND_START, RAND_END);
	player1 = changeBallStatus(player1, get_black);
	broadcast(player1, player2, 1);
	return player1;
}

int movePlayer2(int player1, int player2) {
	int get_black = getRandomBalls(RAND_START, RAND_END);
	player2 = changeBallStatus(player2, get_black);
	broadcast(player1, player2, 2);
	return player2;
}

int isResponseValid(int response, int prevResponse) {
	if (prevResponse == 0) return 0;

	switch (response) {
	case -1: 
		if (prevResponse == 2)
			return 0;
		break;
	case -2:
		if (prevResponse == 1)
			return 0;
		break;
	case 3: break;
	default: return 0;
	}

	return 1;
}

int calcWinner(int player1, int player2) {
	if		(player1 > player2) return 1;
	else if (player1 < player2) return 2;
	else						return 0;
}

int printWinner(int player1, int player2) {
	switch (calcWinner(player1, player2)) {
	case 0: printf("DRAW, ");   break;
	case 1: printf("WIN P1, "); break;
	case 2: printf("WIN P2, "); break;
	default: printf("FATAL ERROR\n"); exit(1);
	}
	printf("P1 %d, P2 %d\n", player1, player2);
}