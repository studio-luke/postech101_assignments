
#include "stdafx.h"

int cmd_use(VAR** var, int n)
{
	*var = (VAR*)malloc(n * sizeof(float));
}

int cmd_vector(VAR* var, char v_name, int);