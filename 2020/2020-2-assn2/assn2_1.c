// Started at 16:29 11/07/2020
// Code by Studio Luke

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH while(getchar() != '\n');

#define WORD_FILENAME "dic.txt"
#define MAX_WORD_LEN 30
#define LIFE 10

int mystrlen(char str[]) {
	int i = 0;

	while (str[i] != '\0') i++;
	return i;
}

void load_rand_word(char dst[]) {
	int num_word, rand_num_idx;
	int i;
	char buf;

	FILE* f = fopen(WORD_FILENAME, "r");
	if (f == NULL) {
		printf("FATAL ERROR: cannot load %s file...\n");
		printf("Program Terminated\n", WORD_FILENAME);
		exit(1);
	}

	fscanf(f, "%d", &num_word);
	rand_num_idx = rand() % num_word;

	// skip (rand_num_idx + 1) line
	// +1 means first line (num_word) \n letter
	for (i = 0; i < rand_num_idx + 1; i++) {
		do fscanf(f, "%c", &buf);
		while (buf != '\n');
	}

	fscanf(f, "%s", dst);
	if (mystrlen(dst) > MAX_WORD_LEN) {
		printf("FATAL ERROR: the length of a word in %s should be less than 30!\n", WORD_FILENAME);
		printf("(chosen word : % s)\n", dst);
		printf("Program Terminated\n");
		exit(2);
	}
}


int main() 
{
	char prob[MAX_WORD_LEN];
	char guess_tot[MAX_WORD_LEN], guess;
	char used_letter[LIFE];
	int word_len;
	int trial, life, i;
	int hit, win;
	int play_again = 1;

	srand(time(NULL));
	
	while (play_again) {
		printf("Let's play the hangman game!\n");
		
		// Initialize the game settings
		load_rand_word(prob);
		word_len = mystrlen(prob);
		for (i = 0; i < word_len; i++)
			guess_tot[i] = '_';
		guess_tot[i] = '\0';
		for (i = 0; i < LIFE; i++)
			used_letter[i] = '\0';
		life = LIFE;
		trial = 0;
		win = 0;

		while (life > 0) {
			// Print current game info
			printf("\nWord: ");
			for (i = 0; i < word_len; i++)
				printf("%c ", guess_tot[i]);
			printf("\nUsed: ");
			for (i = 0; i < trial; i++)
				printf("%c ", used_letter[i]);
			printf("\nHangman (%d life)", life);

			// Goal Check
			for (i = 0; i < word_len; i++) {
				if (prob[i] != guess_tot[i])
					break;
			}
			if (i == word_len) {
				win = 1;
				break;
			}

			// User guess
			printf(" - Input: ");
			scanf("%c", &guess); FFLUSH;
			
			// Input valid check
			for (i = 0; i < trial; i++)
				if (guess == used_letter[i]) {
					printf("%c: Already inserted characher\n", guess);
					break;
				}
			if (i < trial) continue; 

			// Process the single user guess
			hit = 0;
			for (i = 0; i < word_len; i++) {
				if (guess == prob[i]) {
					guess_tot[i] = prob[i];
					hit = 1;
				}
			}

			used_letter[trial++] = guess;

			if (!hit) life--;			
		}

		// Game ending message
		printf("\n\n");
		if (win)
			printf("Congratulations!\n");
		else
			printf("Missing failed!\n");
		printf("The answer was %s\n\n", prob);
		
		// Play again
		while (1) {
			printf("Do you want to playg again? (y/n) ");
			scanf("%c", &guess); FFLUSH;
			if (guess == 'y' || guess == 'Y')
				break;
			else if (guess == 'n' || guess == 'N') {
				play_again = 0;
				break;
			}
			else printf("Invalid input! ");
		}
	}
	printf("Good bye!\n");
}