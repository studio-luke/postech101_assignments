#ifndef STDAFX_H
#define STDAFX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FFLUSH while(getchar() != '\n')

typedef struct variable {
	float** dat;
	int row;
	int col;
	int is_defined;
} VAR;

int cmd_use(VAR** var, int n);

#endif
