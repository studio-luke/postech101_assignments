#include<stdio.h>
#include<math.h>

//  Function Declarations

float cal_area(float x1, float y1, float x2, float y2,
			   float x3, float y3);
int is_ccw(float x1, float y1, float x2, float y2,
		   float x3, float y3);

int main()
{
//  Local Declarations
	int i, n, pre_direction, direction1, direction2;
	float x0, y0, x1, y1, x2, y2, x3, y3,
		  area;

// Statements
	while (1) {
		//  Get the Number of Vertices
		printf("Enter the number of vertices (>2): ");
		scanf("%d", &n);
		
		//  Invalid Input
		if (n <= 2)
		{
			printf("The number of vertices should be more than 2\n\n");
			continue;
		}
		break;
	}

	//  Get Initial 3 Coordinates
	printf("Input the value x and y of P1: ");
	scanf("%f %f", &x0, &y0);
	printf("Input the value x and y of P2: ");
	scanf("%f %f", &x1, &y1);
	printf("Input the value x and y of P3: ");
	scanf("%f %f", &x2, &y2);
	area = cal_area(x0, y0, x1, y1, x2, y2);

	//  Triangle
	if (n == 3) {
		printf("Area of %d-polygon(convex) : %.2f\n", n, area);
		return 0;
	}

	//  n >=4, Decide Clockwise or Counterclockwise
	pre_direction = is_ccw(x0, y0, x1, y1, x2, y2);

	//  Get Additional Coordinates
	for (i = 4; i <= n; i++) {
		printf("Input the value x and y of P%d: ", i);
		scanf("%f %f", &x3, &y3);

		//  Judge Vector Direction ( Clockwise or Counterclockwise )
		direction1 = is_ccw(x1, y1, x2, y2, x3, y3);
		direction2 = is_ccw(x2, y2, x3, y3, x0, y0);

		//  Direction Discords
		if (direction1 != pre_direction || direction2 != pre_direction) {
			printf("Concave polygon!\n");
			return 0;
		}

		//  Sum Up Area
		area += cal_area(x0, y0, x2, y2, x3, y3);

		// Renew Data
		x1 = x2;
		y1 = y2;
		x2 = x3;
		y2 = y3;
	}
	printf("Area of %d-polygon(convex) : %.2f\n", n, area);

	return 0;
}  //  main

/*  ============================= cal_area ==============================
	When three coordinates are presented,
	this function calculates the area of a triangle three points consist.
		Pre		three coordinates to be taken
		Post	Returns the area
*/

float cal_area(float x1, float y1, float x2, float y2,
			   float x3, float y3)
{
//  Statement
	return abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)) / 2.0;
}  //  cal_area

 /*  =============================== is_ccw =================================
	When three coordinates are presented,
	this function judges directonal relation between subsequent two vectors
	that three points consist.
		Pre		three coordinates to be taken
		Post	Returns promised number that represents clockwise or counterclockwise
 */

int is_ccw(float x1, float y1, float x2, float y2,
		   float x3, float y3)
{
//  Local Declarations
	int direction = 0;
	float a1, b1, a2, b2, ccw;
	
// Statements
	// Generate Elements of Two Vectors
	a1 = x2 - x1;
	b1 = y2 - y1;
	a2 = x3 - x2;
	b2 = y3 - y2;

	// Cross Product
	ccw = a1*b2 - a2*b1;

	// Decision Number
	if (ccw >= 0)
		direction = -1;
	else if (ccw <= 0)
		direction = 1;

	return direction;
}