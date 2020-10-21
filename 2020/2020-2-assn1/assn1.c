// Started on 10/21/2020 13:20
// Code by Studio Luke

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH while(getchar() != '\n');
#define MAX_TRIES 10

void draw_line() { 
	for (int i = 0; i < 31; i++)
		printf("#");
	printf("\n");
}

void print_tries_status(int tries) {
	int i;
	for (i = 0; i < tries; i++)
		printf("бр ");
	for (i = 0; i < MAX_TRIES - tries; i++)
		printf("бс ");
	printf("\n");
}

int get_random_num() {
	while (1) {
		int num = rand() % 900 + 100;
		if (is_valid_num(num))
			return num;
	}
} 

int is_valid_num(int num) {
	int one = num % 10;
	int ten = (num / 10) % 10;
	int hund = num / 100;
	if ((100 <= num && num < 1000) && 
		(one != ten && ten != hund && hund != one))
		return 1;
	else return 0;
}

int is_digit_exist(int num, int digit) {
	while (num > 0) {
		if (digit == num % 10)
			return 1;
		num /= 10;
	}
	return 0;
}

void compare(int comp, int user, int* strike, int* ball) {
	int comp_copied = comp;
	*strike = *ball = 0;
	while (comp > 0) {
		if (comp % 10 == user % 10)
			*strike += 1;
		else if (is_digit_exist(comp_copied, user % 10))
			*ball += 1;
		comp /= 10;
		user /= 10;
	}
}

/* Substitute of given function 'print_comparsion_results()'
 *  - Call compare() function to print the comparsion result
 *  - if out, increase out count
 *  - if user quit the game, set out 3
 *  - if user got the answer return 1, otherwise, return 0 
 */
int judge_user_input(int comp, int user, int *out) {
	int strike = 0, ball = 0;

	// if user guess is invalid, do not compare, let strike & ball 0.
	if (is_valid_num(user))
		compare(comp, user, &strike, &ball);
	printf("[%d Strike %d Ball] ", strike, ball);

	// Print Messages
	if (user == -1)
		*out = 3;
	else if (!is_valid_num(user))
		printf("Wrong input!!");
	else if (strike + ball == 0) {
		*out += 1;
		printf("%d Out!!", *out);
	}
	printf("\n\n");

	if (strike == 3)
		return 1;
	else return 0;
}

int main() {
	int inning = 0;
	int tries, out, score, total_score = 0, win;
	int guess, answer, one, ten, hund;
	int run_game = 1;
	char y_or_n;
	
	draw_line();
	printf("         Baseball Game         \n");
	draw_line(); printf("\n");
	srand(time(NULL));

	while (run_game) {
		answer = get_random_num();
		tries = out = 0;
		win = 0;

		inning++;
		printf("<<< Inning #%d >>>\n", inning);
		draw_line();
		while (tries < 10 && out < 3) {
			print_tries_status(tries);
			printf("Enter your guess(-1 to quit): ");
			scanf("%d", &guess); FFLUSH;
			if (judge_user_input(answer, guess, &out)) {
				win = 1;
				break;
			}
			tries++;
		}

		if (win) {
			printf("Right!!\n");
			score = 100 - 10 * tries;
		}
		else {
			printf("The answer is %d.\n", answer);
			score = 0;
		}
		printf("Your score is %d points.\n", score);
		while (1) {
			printf("Do you want to play again? (y/n) ");
			scanf("%c", &y_or_n); FFLUSH;
			if (y_or_n == 'y' || y_or_n == 'Y')
				break;
			else if (y_or_n == 'n' || y_or_n == 'N') {
				run_game = 0;
				break;
			}
		}
		total_score += score;
		printf("\n\n");
	}

	printf("Your average score is %.1f points.", (float)total_score / inning);
	printf("Thanks for playing!\n");
	printf("Press Enter to continue..."); FFLUSH;
}