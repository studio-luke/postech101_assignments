/* We have made a rectangular parallelepiped by using unit cubes
   and painted its exterior.
   This program accounts the number of cubes
   which have only  two painted sides.
   		Written by : 20170697 ±è½ÂÀÏ
		Date : 2017-03-20
 */

#include<stdio.h>

#define FFLUSH while(getchar() != '\n');

// Function Declarations

int accountBlocks (int width, int height, int depth);

int main()
{
// Local Declarations
	int width, height, depth, numberofblock;

// Statements
	// Get the data of the rectangular parrallelepiped
	printf("Input width, height, depth: ");
	scanf("%d %d %d", &width, &height, &depth); FFLUSH;
	
	// Account the number of wanted cubes and print it
	numberofblock = accountBlocks(width,height,depth);
	printf("Result : %d\n", numberofblock);
	
	printf("Press Enter to quit..."); FFLUSH;
	return 0;
}	// main

/* =================accountBlocks=====================
   
   This function calculates the number of wanted cubes
   with a simple formula
   		Pre   a, b, c contains integers
		Post  Returns the number of wanted cubes
 */
int accountBlocks(int a, int b, int c)
{
// Local Declarations	
	int result;

// Statements
	result = 4*(a-2)+4*(b-2)+4*(c-2);
		
	return result;
}	// main

