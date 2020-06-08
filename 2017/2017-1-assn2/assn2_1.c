/* Guess the number the program has randomly chosen!
   Rule : You can input 4-digit number in each try to guess the number!
		  
		  3 2 4 8  = > Your Input            If certain digits of number corresponds
		 (4 2 4 5) = > Answer                with digits of the answer in same position,
		 ---------						     the program will print that number.
		  1 2 4 7  = > Program's Output      Otherwise, the program will print random number
											 other than the digit you've input and the digit of the answer.
		  Have you understand? Then GUESS the number in minimal tries!  
		       Written by : Kim Seungil
			   Date : 2017-04-04
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define FFLUSH while(getchar() != '\n')

// Function Declarations

int init_num(void);
int is_correct(int guessingnum, int answer, int *newnumber);
void extract_digit(int num, int *first, int *second, int *third, int *fourth);
int remake_num(int object_first, int object_second, int object_third, int object_fourth,
			   int answer_first, int answer_second, int answer_third, int answer_fourth);
int remake_digit(int comparative_num1, int comparative_num2);
void is_restart(char *yesorno);

int main()
{
// Local Declarations
	int i, guessnum, answernum, yesorno, newnumber,
		decision1, decision2, decision3, decision4;
// Statements			
	while (1) {
		// Choose Random number
		srand(time(NULL));
		answernum = init_num();
		
		// Game Start!
		printf("Number Guessing Game!\n");
		i = 1;
		while (1) {
			printf("[Trial %d]\n", i);
			printf("Input 4 digits<0 to quit> -> ");
			scanf("%d", &guessnum); FFLUSH;

			// Quit
			if (guessnum == 0) {
				printf("Hmm... You didn't find an answer\n");
				printf("Answer is %d\n", answernum);
				yesorno = 3;
				is_restart(&yesorno);
				break;
			}

			// Valid Input
			else if (guessnum >= 1000 && guessnum <= 9999) {
				if (is_correct(guessnum, answernum, &newnumber))  /* Function Call
																	 Correct : Return 1
																	 Incorrect : Return 0, Make New Number */
				{
					printf("Congratulations! You got a correct answer!\n");
					yesorno = 3;
					is_restart(&yesorno);
					break;
				}
				printf("Output digits -> %d\n\n", newnumber);
				i++;
				continue;
			}

			// Invalid Input
			else {
				printf("\n");
				i++;
				continue;
			}
		}
		
		// Decide Exit or Not
		printf("\n\n");
		if (yesorno == 2)
			continue;
		else
			break;
	}
	printf("Press Enter to quit..."); FFLUSH;
	return 0;
} // main

/* ========================================== init_num ==================================================
	Choose a random 4-digit number.
		Pre		Set seed value of random generator
		Post	Returns random number
*/
int init_num(void)
{
// Local Declaration
	int randnum, range;

// Statements
	range = (9999 - 1000) + 1;
	randnum = rand() % range + 1000;
	return randnum;
}  // init_num

/*  ========================================  is_correct ==================================================
	Examine whether each digit in your input and the answer corresponds
		Pre		Random number and user's input number to be taken
		Post	If all 4 digits equal, retruns 1
				If not, returns 0 and produce new number.
*/

int is_correct(int object, int answer, int *newnumber)
{
// Local Declaration
	int o_first, o_second, o_third, o_fourth,
		a_first, a_second, a_third, a_fourth,
		answerDecision;

// Statements
	// Decide Correct or Not
	if (object == answer)
		answerDecision = 1;
	else {
		//  Extract Digits from Integer
		extract_digit(object, &o_first, &o_second, &o_third, &o_fourth);
		extract_digit(answer, &a_first, &a_second, &a_third, &a_fourth);
	
		*newnumber = remake_num(o_first, o_second, o_third, o_fourth,
				   				a_first, a_second, a_third, a_fourth);
		answerDecision = 0;
	}
	return answerDecision;
}  //  is_correct

/*  ====================================== extract_digit ==================================================
	Extract each four digit from a integer.
		Pre		A 4-digit integer and address of variables that can contain each digit to be taken
		Post	Each digits placed in each variable
*/

void extract_digit(int num, int *first, int *second, int *third, int *fourth)
{
//Statements
	*first = (num - num % 1000) / 1000;
	*second = (num % 1000 - num % 100) / 100;
	*third = (num % 100 - num % 10) / 10;
	*fourth = num % 10;
}  //  extract_digit

/* ========================================= remake_num ==================================================
	Produce a random 4-digit number	in given rule :
	 the random number should not coincide with	certan number(digit in answer, digit in your input)
		Pre		Decision number (0 or 1) and each required digit to be taken
		Post	Returns newly produced random number
*/

int remake_num(int o_first, int o_second, int o_third, int o_fourth,
			   int a_first, int a_second, int a_third, int a_fourth)
{
// Local Declarations
	int newnum1, newnum2, newnum3, newnum4;

// Statements
	//  Produce Digits
	if (o_first == a_first)
		newnum1 = a_first;
	else
		while (1) {
			newnum1 = rand() % 9 + 1;
			if (newnum1 == a_first || newnum1 == o_first)
				continue;
			break;
		}

	newnum2 = remake_digit(a_second, o_second);
	newnum3 = remake_digit(a_third, o_third);
	newnum4 = remake_digit(a_fourth, o_fourth);

	//  Make Demicial Number
	return newnum1 * 1000 + newnum2 * 100 + newnum3 * 10 + newnum4;
}  //  remake_num

/*  ======================================== remake_digit =================================================
	To make a 4-digit demicial number, this function randomly produces each four digit,
	avoiding two digit : digit of answer, digit of your input
		Pre		Two digits and decision number(0 or 1) to be taken
		Post	Returns a new digit
*/

int remake_digit(int num1, int num2)
{
// Local Declaration
	int newnum;

// Statements
	if (num1 == num2)
		newnum = num1;
	else
		// Choose Random Digit Until It Satisfies Rules
		while (1) {
			newnum = rand() % 10;
			if (newnum == num1 || newnum == num2)
				continue;
			break;
		}
	return newnum;
}  //  remake_digit

/*  ========================================= is_restart ==================================================
	Get user's decision whether you would quit the program or not.
	Then convert user's decision to promised numbers.
		Pre		Nothing
		Post	Get user's decision (yes or not) and place promised numbers
*/

void is_restart(char *yesorno)
{
// Local Declaration
	char decision;

// Statements
	while (*yesorno == 3) {
		// Get User's Decision
		printf("Try again <y/n> -> ");
		scanf("%c", &decision); FFLUSH;

		// Convert Character to Number
		if (decision == 'n' || decision == 'N')
			*yesorno = 1;
		else if (decision == 'y' || decision == 'Y')
			*yesorno = 2;
		// Invalid Input
		else
			*yesorno = 3;
	}
}  //  is_restart