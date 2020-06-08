/*	This Program Generates a map with some objects put in the map
	and show us a portion of the whole map.
	You can move the portion of view by using some keys(h, j, k, l, etc)
		Written by : Kim Seung il
		Date : 2017-04-26
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"map.h"

#define FFLUSH while(getchar() != '\n')

// Function Declaration

void CreateMap(char main_map[][MAP_COL]);
void DrawCircle(int center_row, int center_col, int radius,
	char main_map[][MAP_COL]);
void DrawSquare(int top_left_row, int top_left_col,
	int bottom_right_row, int bottom_right_col, char main_map[][MAP_COL]);
void PrintMap(char main_map[][MAP_COL], int current_row, int current_col);
int doOrder(char order, char main_map[][MAP_COL], int* current_row, int* current_col);

int main()
{
// Local Declaration
	int current_row, current_col;
	char main_map[MAP_ROW][MAP_COL];
	char order;
	int loop = 1;

// Statements
	CreateMap(main_map);
	
	// Random Start Position
	srand(time(NULL));
	current_row = rand() % MAP_ROW;
	current_col = rand() % MAP_COL;

	PrintMap(main_map, current_row, current_col);

	// Get Order Input for Play
	while (loop) {
		printf("   * Uppercase to move 10 step * \n");
		printf("[h: left, j: down, k: up, l: right\n");
		printf(" c: center, q: quit ]\n");
		printf(">>> ");
		scanf("%c", &order); FFLUSH;
		loop = doOrder(order, main_map, &current_row, &current_col);
	}

	return 0;
} // main

/*  This function initializes the 2-dimentional array
	and arrange some objects in the map.
		Pro		None
		Post	Creates a game map
*/

void CreateMap(char main_map[][MAP_COL])
{
// Local Declaraton
	int i, j;

// Statements
	// Initialize
	for (i = 0; i < MAP_ROW; i++)
		for (j = 0; j < MAP_COL; j++)
			main_map[i][j] = ' ';
	
	// Arrange Objects
	DrawCircle(MAP_ROW / 2, MAP_COL / 2, RADIUS, main_map);
	DrawSquare(10, 10, 20, 40, main_map);
	DrawSquare(25, 15, 30, 30, main_map);
}  //  CreateMap

/*	This function puts a circle on the map.
	(Mark with 'c')
		Pro		None
		Post	Creates a circular object in the map
*/

void DrawCircle(int center_row, int center_col, int radius,
	char main_map[][MAP_COL])
{
// Local Declaration
	int i, j;

// Statements
	for (i = center_row - radius; i < center_row + radius + 1; i++)
		for (j = center_col - radius; j < center_col + radius + 1; j++)
			if ((i - center_row)*(i - center_row) + (j - center_col)*(j - center_col) <= radius*radius)
				main_map[i][j] = 'c';
}  //  DrawCircle

/*	This function puts a rectangular on the map.
	(Mark with 's')
	Pro		None
	Post	Creates a rectangular object in the map
*/

void DrawSquare(int top_left_row, int top_left_col,
	int bottom_right_row, int bottom_right_col, char main_map[][MAP_COL])
{
// Local Declaration
	int square_row = bottom_right_row - top_left_row;
	int square_col = bottom_right_col - top_left_col;
	int i, j;

// Statements
	for (i = top_left_row; i < top_left_row + square_row; i++)
		for (j = top_left_col; j < top_left_col + square_col; j++)
			main_map[i][j] = 's';
}  //  DrawSquare

/*	This function clears the screen
	and print the view of given position.
	And below it indicates the location of center of the view.
		Pro		Get location of the center of the view 
		Post	Prints the required view of the map
*/

void PrintMap(char main_map[][MAP_COL], int current_row, int current_col)
{
// Local Declarations
	int i, j;

// Statements
	system("cls");
	for (i = 0; i < VIEW_COL + 2; i++) 
		printf("-");  // Print Boundary of the View
	printf("\n");

	for (i = current_row - VIEW_ROW / 2; i < current_row + VIEW_ROW / 2; i++) {
		printf("|");  // Print Boundary of the View
		for (j = current_col - VIEW_COL / 2; j < current_col + VIEW_COL / 2; j++) {
			if (0 <= i && i < MAP_ROW && 0 <= j && j < MAP_COL) // Examine Whether Inside of Map or not
				printf("%c", main_map[i][j]);
			else
				printf("x");  // Print 'x' out of Map
		}
		printf("|\n");  // Print Boundary of the View
	}
	
	for (i = 0; i < VIEW_COL + 2; i++)
		printf("-");  // Print Boundary of the View
	printf("\n======= Row: %d, Col: %d =======\n", current_row, current_col); // Indicate Location
}  //  PrintMap 

/*	This function does order users have input,
	move view of map, or quit the program.
		Pro		Get input of user
		Post	Print new map or quit the program
*/

int doOrder(char order, char main_map[][MAP_COL], int* current_row, int* current_col)
{
//  Local Declaration

// Statement
	switch (order) {
	case 'h':
		if (*current_col - 1 >= 0)
			PrintMap(main_map, *current_row, --(*current_col)); // Move View Leftward
		break;
	case 'H':
		if (*current_col - MOVE_STEP >= 0)
			PrintMap(main_map, *current_row, *current_col -= MOVE_STEP);  // Jump View Leftward
		else
			PrintMap(main_map, *current_row, *current_col = 0);  // Not to Escape Map
		break;
	
	case 'j':
		if (*current_row + 1 < MAP_ROW)
			PrintMap(main_map, ++(*current_row), *current_col);  //  Move View Downward
		break;
	case 'J':
		if (*current_row + MOVE_STEP < MAP_ROW)
			PrintMap(main_map, *current_row += MOVE_STEP, *current_col);  //  Jump View Downward
		else
			PrintMap(main_map, *current_row = MAP_ROW - 1, *current_col);
		break;
	
	case 'k':
		if (*current_row - 1 >= 0)
			PrintMap(main_map, --(*current_row), *current_col);  //  Move View Upward
		break;
	case 'K':
		if (*current_row - MOVE_STEP >= 0)
			PrintMap(main_map, *current_row -= MOVE_STEP, *current_col);  // Jump View Upward
		else
			PrintMap(main_map, *current_row = 0, *current_col);
		break;
	
	case 'l':
		if (*current_col + 1 < MAP_COL)
			PrintMap(main_map, *current_row, ++(*current_col));  //  Move View Rightward
		break;
	case 'L':
		if (*current_col + MOVE_STEP < MAP_COL)
			PrintMap(main_map, *current_row, *current_col += MOVE_STEP);  //  Jump View Rightward
		else
			PrintMap(main_map, *current_row, *current_col = MAP_COL - 1);
		break;
	case 'C':
	case 'c':
		PrintMap(main_map, *current_row = MAP_ROW / 2, *current_col = MAP_COL / 2);  //  Move to Center of Map
		break;
	case 'Q':
	case 'q':
		return 0;  //  Quit Program
	
	default:
		PrintMap(main_map, *current_row, *current_col);  // Keep Map
	}
	return 1;
}  //  doOrder