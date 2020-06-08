/*	This program gets the size of map and the number
	and generate mine map and map solution.
		Written by : Kim Seung il
		Date : 2017-04-26
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAP_ROW 20
#define MAP_COL 20

//  Function Declarations

void InputValueExamine(int input_value, int range_start, int range_end);
int GenerateMineMap(int n, int size, char mineMap[][MAP_COL]);
int SaveMineMap(int size, char mineMap[][MAP_COL]);
int PrintSolution(int size, char mineMap[][MAP_COL]);

int main()
{
//  Local Declarations
	char mineMap[MAP_ROW][MAP_COL];
	int mapSize, mineNumber;

//  Statements
	//  Get Data
	printf("Input the size of map: ");
	scanf("%d", &mapSize);
	InputValueExamine(mapSize, 9, 20);
	
	printf("Input the number of mines: ");
	scanf("%d", &mineNumber);
	InputValueExamine(mineNumber, 10, (mapSize - 1)*(mapSize - 1));
	
	//  Generate Map
	srand(time(NULL));
	GenerateMineMap(mineNumber, mapSize, mineMap);
	SaveMineMap(mapSize, mineMap);
	PrintSolution(mapSize, mineMap);

	printf("End of program.\n");
	return 0;
}  //  main

/*	This function examine whether the input data are in the agreeable range.
	If not, it prints error message and quit the program.
		Pro		Get data from user
		Post	If out of range, print error message and quit the program
*/

void InputValueExamine(int data, int start, int end)
{
//  Local Declarations

//  Statements
	if (data < start || data > end) {
		printf("Input value out of range.\n");
		exit(100);
	}
}  //  InputValueExamine

/*	This function generates mine map, in which mines are arranged randomly.
	The function can also examine whether required number of mine are put successfully.
		Pro		Get number of mine and Size of map
		Post	Save map in the array
*/

int GenerateMineMap(int n, int size, char mineMap[][MAP_COL])
{
// Local Declarations
	int i, j, k;
	int CheckMineNum = 0;

// Statements
	//  Initialize
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			mineMap[i][j] = '.';

	//  Arrange Random Mine
	for (k = 0; k < n; k++) {
		while (1) {
			i = rand() % size;
			j = rand() % size;
			if (mineMap[i][j] == '*')
				continue;
			else {
				mineMap[i][j] = '*';
				break;
			}
		}
	}

	// Debugging
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (mineMap[i][j] == '*')
				CheckMineNum++;
	if (CheckMineNum == n)
		return 0;
	else
		return 1;
} //  GenerateMineMap

/*	This function prints mine map through text file.
		Pro		Mine map Generated
		Post	Make a text file 
*/

int SaveMineMap(int size, char mineMap[][MAP_COL])
{
//  Local Declaration
	FILE *MapOutput;
	int i, j;
	char character;

//  Statements
	// Open File
	MapOutput = fopen("minemap.txt", "w");
	if ( MapOutput == NULL) {
		printf("Cannot Print File");
		return 1;
	}

	//  Print Size of Map
	fprintf(MapOutput, "%d\n", size);

	//  Print Mine Map 
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fprintf(MapOutput, "%c", mineMap[i][j]);
		}
		fprintf(MapOutput, "\n");
	}
	

	//  Close File
	fclose(MapOutput);
	return 0;
}

/*	This function generates Solution Map,
	which contains informations of number to guess the location of mines
	and prints it through text file.
		Pro		Mine map generated 
		Post	Save solution map in the array and make text file
*/

int PrintSolution(int size, char mineMap[][MAP_COL])
{
// Local Declaration
	FILE *solution;
	int i, j, k, l, detecter;
	char character;

// Statements
	//  Open File
	solution = fopen("mapsol.txt", "w");
	if (solution == NULL) {
		printf("Cannot Print File");
		return 1;
	}

	//  Make Solution Map
	for (i = 0; i < size; i++) 
		for (j = 0; j < size; j++)					//  Main Loop
		{	if (mineMap[i][j] == '*')
				continue;
			detecter = 0;  //  detecter is number of mines around a element
			for (k = -1; k <= 1; k++) {
				if (i + k < 0 || i + k >= size)
					continue;   //  Prevent Tracking Non-array Elements
				for (l = -1; l <= 1; l++)			//  Sub Loop - to detect mine around
				{	if (j + l < 0 || j + l >= size)
						continue;
					if (mineMap[i + k][j + l] == '*')
						detecter++; 
				}
			}
			mineMap[i][j] = detecter + 48;	//  The ASCII Code of '0' is 48.
		}

	//  Print Size of Map
	fprintf(solution, "%d\n", size);

	//  Print Solution Map
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fprintf(solution, "%c", mineMap[i][j]);
		}
		fprintf(solution, "\n");
	}
	
	//  Close File
	fclose(solution);
	return 0;
}  //  PrintSolution