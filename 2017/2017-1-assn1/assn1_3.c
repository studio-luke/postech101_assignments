/* This program gets a binary number
   and converts it to a decimal number.
   		Written by : 20170697 ±è½ÂÀÏ
		Date : 2017-03-20
 */

#include<stdio.h>

#define FFLUSH while(getchar() != '\n');

// Function Declarations 
int changeBtoD(int binaryNum);

int main()
{
// Local Declarations
	int binaryNum, decimalNum;

// Statement
	// Get a binary number
	printf("Input a 5-bit binary number: ");
	scanf("%d", &binaryNum); FFLUSH;
	
	// Convert the binary to the demicial and print it
	decimalNum = changeBtoD(binaryNum);
	printf("The binary number %d is a decimal number %d\n", binaryNum, decimalNum);

	printf("Press Enter to quit..."); FFLUSH;
	return 0;
} // main

/* =============================ChangeBtoD==================================
   This function converts a binary number to a demicial number.
   		Pre  num contains an integer in a binary form
		Post Returns converted demicial number.
 */
int changeBtoD(int num)
{
// Local declaration
	int first, second, third, fourth, fifth;

// Statements
	// Extract each figure of binary number
	first = num%10;
	second = (num%100-num%10)/10;
	third = (num%1000-num%100)/100;
	fourth = (num%10000-num%1000)/1000;
	fifth = (num-num%10000)/10000;

	// Make it to a  demicial form
	return fifth*16+fourth*8+third*4+second*2+first;
}	// changeBtoD
