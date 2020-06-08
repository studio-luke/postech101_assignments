/* This program reads initials of one's name
   and prints their ASCII code and their lowercase.
   		Written by : 20170697 ±è½ÂÀÏ
		Date : 2017-03-20 
 */

#include<stdio.h>

int main()
{
// Local Declarations
	char firstLetter, secondLetter, thirdLetter;

// Statements
	// Get initials
	printf("Input your initials with white space: ");
	scanf("%c %c %c", &firstLetter, &secondLetter, &thirdLetter);
	
	// Print results
	printf("ASCII code of your input : %d %d %d\n", firstLetter, secondLetter, thirdLetter);
	printf("Converted output : %c %c %c\n", firstLetter+32, secondLetter+32, thirdLetter+32);

	return 0;
} // main
