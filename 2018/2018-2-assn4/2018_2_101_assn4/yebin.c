#include <stdio.h>
#include <string.h>
typedef struct
{
	char name[100];
	float ***data;
	int C, H, W;
	int is_normalized;
}CUBIC;

void choice1(CUBIC ***images, int *cnt);
void printlist(CUBIC **images, int *cnt, CUBIC **filters, int *fcnt);
void choice2(CUBIC **images, int *cnt, CUBIC **filters);
void choice3(CUBIC ***images, int *cnt, CUBIC **filters, int *fcnt);
void choice4(CUBIC ***filters, int *fcnt);
void choice5(CUBIC **images, int *cnt, CUBIC ***filters, int *fcnt);
void choice7(CUBIC **images, int *cnt, CUBIC **filters);
void choice8(CUBIC **images, int *cnt, CUBIC **filters);
void choice9(CUBIC ***images, int *cnt, CUBIC**filters, int*fcnt);

int main(void)
{
	CUBIC **images = NULL;
	CUBIC **filters = NULL;

	int input;
	int cnt = 0;
	int fcnt = 0;

	images = (CUBIC **)malloc(sizeof(CUBIC*));
	filters = (CUBIC **)malloc(sizeof(CUBIC*));

	while (1) {
		printf("============================\n");
		printf("|     IMAGE CONVOLUTION    |\n");
		printf("|   1. Image load          |\n");
		printf("|   2. Image save          |\n");
		printf("|   3. Image remove        |\n");
		printf("|   4. Filter load         |\n");
		printf("|   5. Filter remove       |\n");
		printf("|   6. Print               |\n");
		printf("|   7. Normalize           |\n");
		printf("|   8. Denormalize         |\n");
		printf("|   9. lmage convolution    |\n");
		printf("|   10. Quit               |\n");
		printf("============================\n");
		printf("Enter number :");
		scanf("%d", &input);

		if (input == 1)
			choice1(&images, &cnt);
		else if (input == 2)
			choice2(images, &cnt, filters);
		else if (input == 3)
			choice3(&images, &cnt, filters, &fcnt);
		else if (input == 4)
			choice4(&filters, &fcnt);
		else if (input == 5)
			choice5(images, &cnt, &filters, &fcnt);
		else if (input == 6)
			printlist(images, &cnt, filters, &fcnt);
		else if (input == 7)
			choice7(images, &cnt, filters);
		else if (input == 8)
			choice8(images, &cnt, filters);
		else if (input == 9)
			choice9(&images, &cnt, filters, &fcnt);
		else if (input == 10)
		{
			free(images);
			free(filters);
			break;
		}
	}

	return 0;
}

void choice1(CUBIC ***images, int *cnt)
{
	char filename[20] = { NULL };
	char filename1[20] = { NULL };
	int *search;
	int i, j, k = 0;
	FILE *infile;
	int c;
	int h, w, range;
	char temp[100] = { NULL };
	char a;
	CUBIC* image = (CUBIC*)malloc(sizeof(CUBIC));
	(*images) = (CUBIC **)realloc((*images), (*cnt + 1) * sizeof(CUBIC*));

	printf("Enter image filename : ");
	getchar();
	scanf("%s", filename);

	infile = fopen(filename, "r");
	fscanf(infile, "%c%d %d %d %d", &a, &c, &w, &h, &range);

	strcpy(filename1, filename);
	search = strchr(filename1, '.');
	*search = '\0';
	strcpy(temp, filename1);
	strcpy(image->name, temp);
	image->C = c;
	image->H = h;
	image->W = w;
	image->is_normalized = 0;

	(*cnt)++;
	image->data = (float***)malloc(sizeof(float**)*c);
	for (i = 0; i < c; i++)
	{
		image->data[i] = (float**)malloc(sizeof(float*)*w);
		for (j = 0; j < w; j++)
		{
			image->data[i][j] = (float*)malloc(sizeof(float)*h);
		}
	}

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			for (k = 0; k < c; k++)
			{
				fscanf(infile, "%f", &(image->data[k][j][i]));
			}
		}
	}
	//만약 images안에 아무것도 없다면 동적할당을 하여 메모리를 만들어 준후 넣는다. 그리고 images안에 값이 있다면 동적할당을 하여 자리를 새로 만들어 준후 넣는다.(realloc)
	(*images)[*cnt - 1] = image;
	fclose(infile);
}
void printlist(CUBIC **images, int *cnt, CUBIC **filters, int*fcnt)
{
	printf("==========IMAGE LIST===========\n");
	int i;
	for (i = 0; i < (*cnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]", i, images[i]->name, images[i]->H, images[i]->W, images[i]->C);
		if (images[i]->is_normalized == 1)
			printf("-normalized");
	}
	printf("\n==========FILTER LIST==========\n");

	for (i = 0; i < (*fcnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, (filters[i])->name, filters[i]->H, filters[i]->W, filters[i]->C);
	}
}
void choice2(CUBIC **images, int *cnt, CUBIC **filters)
{
	int b;
	int i, j, k = 0;
	int input;
	int range;
	char a;
	FILE*outfile;
	char filename2[20];
	int *search;

	for (i = 0; i < *cnt; i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, images[i]->name, images[i]->H, images[i]->W, images[i]->C);
	}
	printf("Enter the number of image to save : ");
	getchar();
	scanf("%d", &input);
	printf("Enter the filename of image to save : ");
	getchar();
	scanf("%s", filename2);
	outfile = fopen(filename2, "w");
	fprintf(outfile, "%c%d %d %d %d\n", 'P', images[input]->C, images[input]->W, images[input]->H, 255);

	for (i = 0; i < images[input]->H; i++)
	{
		for (j = 0; j < images[input]->W; j++)
		{
			for (k = 0; k < images[input]->C; k++)
			{
				b = (int)images[input]->data[k][j][i];
				if (b < 0)
				{
					b = 0;
				}
				else if (b > 255)
				{
					b = 255;
				}
				fprintf(outfile, "%d ", b);
			}

		}
	}

	fclose(outfile);

}
void choice3(CUBIC ***images, int *cnt, CUBIC **filters, int *fcnt)
{
	int fileindex;
	int i, j, k;
	printlist(*images, cnt, filters, fcnt);
	printf("Enter the number of image to remove : ");
	getchar();
	scanf("%d", &fileindex);

	for (i = 0; i < (*images)[fileindex]->C; i++)
	{
		for (j = 0; j < (*images)[fileindex]->W; j++)
		{
			free((*images)[fileindex]->data[i][j]);
		}
		free((*images)[fileindex]->data[i]);
	}

	free((*images)[fileindex]->data);
	free((*images)[fileindex]);
	(*cnt)--;

	for (i = fileindex; i < *cnt; i++)
	{
		(*images)[i] = (*images)[i + 1];
	}

	((*images)) = (CUBIC **)realloc(((*images)), (*cnt) * sizeof(CUBIC*));

}
//void choice4(CUBIC *filter, CUBIC **filters, int *cnt)
//{
//   char filename[20] = { NULL };
//   char filename1[20] = { NULL };
//   int *search;
//   int i, j, k = 0;
//   FILE *infile;
//   int c;
//   int h, w, range;
//   char temp[100] = { NULL };
//   char a;
//   filter = (CUBIC*)malloc(sizeof(CUBIC));
//   (filters) = (CUBIC **)realloc((filters), (*cnt + 1) * sizeof(CUBIC*));
//
//   printf("Enter filter filename : ");
//   getchar();
//   scanf("%s", filename);
//   infile = fopen(filename, "r");
//   fscanf(infile, "%c%d %d %d %d", &a, &c, &w, &h, &range);
//   (filters)[*cnt] = filter;
//   strcpy(filename1, filename);
//   search = strchr(filename1, '.');
//   *search = '\0';
//   strcpy(temp, filename1);
//   strcpy(filter->name, temp);
//   filter->C = c;
//   filter->H = h;
//   filter->W = w;
//
//   (*cnt)++;
//   filter->data = (float***)malloc(sizeof(float**)*c);
//   for (i = 0; i < c; i++)
//   {
//      filter->data[i] = (float**)malloc(sizeof(float*)*w);
//      for (j = 0; j < w; j++)
//      {
//         filter->data[i][j] = (float*)malloc(sizeof(float)*h);
//      }
//   }
//   for (i = 0; i < h; i++)
//   {
//      for (j = 0; j < w; j++)
//      {
//         for (k = 0; k < 1; k++)
//         {
//            fscanf(infile, "%f", &(filter->data[k][j][i]));
//         }
//      }
//   }
//   //만약 images안에 아무것도 없다면 동적할당을 하여 메모리를 만들어 준후 넣는다. 그리고 images안에 값이 있다면 동적할당을 하여 자리를 새로 만들어 준후 넣는다.(realloc)
//   fclose(infile);
//}

void choice4(CUBIC ***filters, int *fcnt)
{
	char filename[20] = { NULL };
	char filename1[20] = { NULL };
	int *search;
	int i, j, k = 0;
	FILE *infile;
	int c;
	int h, w, range;
	char temp[100] = { NULL };
	char a;
	CUBIC* filter = (CUBIC*)malloc(sizeof(CUBIC));
	(*filters) = (CUBIC **)realloc((*filters), (*fcnt + 1) * sizeof(CUBIC*));

	printf("Enter filter filename : ");
	getchar();
	scanf("%s", filename);

	infile = fopen(filename, "r");
	fscanf(infile, "%c%d %d %d %d", &a, &c, &w, &h, &range);

	strcpy(filename1, filename);
	search = strchr(filename1, '.');
	*search = '\0';
	strcpy(temp, filename1);
	strcpy(filter->name, temp);
	filter->C = c;
	filter->H = h;
	filter->W = w;
	filter->is_normalized = 0;

	(*fcnt)++;
	filter->data = (float***)malloc(sizeof(float**)*c);
	for (i = 0; i < c; i++)
	{
		filter->data[i] = (float**)malloc(sizeof(float*)*w);
		for (j = 0; j < w; j++)
		{
			filter->data[i][j] = (float*)malloc(sizeof(float)*h);
		}
	}

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			for (k = 0; k < c; k++)
			{
				fscanf(infile, "%f", &(filter->data[k][j][i]));
			}
		}
	}
	//만약 images안에 아무것도 없다면 동적할당을 하여 메모리를 만들어 준후 넣는다. 그리고 images안에 값이 있다면 동적할당을 하여 자리를 새로 만들어 준후 넣는다.(realloc)
	(*filters)[*fcnt - 1] = filter;
	fclose(infile);
}
void choice5(CUBIC **images, int *cnt, CUBIC ***filters, int *fcnt)
{
	int fileindex;
	int i, j, k;
	printlist(images, cnt, *filters, fcnt);
	printf("Enter the number of filter to remove : ");
	getchar();
	scanf("%d", &fileindex);

	for (i = 0; i < (*filters)[fileindex]->C; i++)
	{
		for (j = 0; j < (*filters)[fileindex]->W; j++)
		{
			free((*filters)[fileindex]->data[i][j]);
		}
		free((*filters)[fileindex]->data[i]);
	}

	free((*filters)[fileindex]->data);
	free((*filters)[fileindex]);
	(*fcnt)--;

	for (i = fileindex; i < *fcnt; i++)
	{
		(*filters)[i] = (*filters)[i + 1];
	}

	((*filters)) = (CUBIC **)realloc(((*filters)), (*fcnt) * sizeof(CUBIC*));

}

void choice7(CUBIC **images, int *cnt, CUBIC **filters)
{
	int i, j, k = 0;
	int input = 0;

	for (i = 0; i < (*cnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, images[i]->name, images[i]->H, images[i]->W, images[i]->C);//여기서 안넘어가용..
	}
	printf("Enter the number of image to normalized  : ");
	getchar();
	scanf("%d", &input);
	for (i = 0; i < images[input]->H; i++)
	{
		for (j = 0; j < images[input]->W; j++)
		{
			for (k = 0; k < images[input]->C; k++)
			{
				(images[input]->data[k][j][i]) = (images[input]->data[k][j][i]) / 128 - 1;

			}
		}
	}
	images[input]->is_normalized = 1;
}

void choice8(CUBIC **images, int *cnt, CUBIC **filters)
{
	int i, j, k = 0;
	int input = 0;

	for (i = 0; i < (*cnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, images[i]->name, images[i]->H, images[i]->W, images[i]->C);//여기서 안넘어가용..
	}
	printf("Enter the number of image to denormalized  : ");
	getchar();
	scanf("%d", &input);
	for (i = 0; i < images[input]->H; i++)
	{
		for (j = 0; j < images[input]->W; j++)
		{
			for (k = 0; k < images[input]->C; k++)
			{
				(images[input]->data[k][j][i]) = ((images[input]->data[k][j][i]) + 1) * 128;


			}
		}
	}
	images[input]->is_normalized = 0;
}
void choice9(CUBIC ***images, int *cnt, CUBIC**filters, int*fcnt)
{
	CUBIC *image = (CUBIC *)malloc(sizeof(CUBIC));
	int i, j, k, m, n = 0;
	int imageindex, filterindex;
	for (i = 0; i < (*cnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, (*images[i])->name, (*images[i])->H, (*images[i])->W, (*images[i])->C);
	}
	printf("Enter the number of image to convolve : ");
	getchar();
	scanf("%d", &imageindex);
	for (i = 0; i < (*cnt); i++)
	{
		printf("%d. %s  [H: %d, W: %d, C: %d]\n", i, (filters[i])->name, filters[i]->H, filters[i]->W, filters[i]->C);
	}
	printf("Enter the number of filter to convolve : ");
	getchar();
	scanf("%d", &filterindex);

	sprintf(image->name, "%s_%s", (*images)[imageindex]->name, filters[filterindex]->name);

	image->C = (*images)[imageindex]->C;
	image->H = (*images)[imageindex]->H - filters[filterindex]->H + 1;
	image->W = (*images)[imageindex]->W - filters[filterindex]->W + 1;
	image->is_normalized = (*images)[imageindex]->is_normalized;
	image->data = (float***)calloc(image->C, sizeof(float**));

	for (i = 0; i < image->C; i++)
	{
		image->data[i] = (float**)calloc(image->W, sizeof(float*));
		for (j = 0; j < image->W; j++)
		{
			image->data[i][j] = (float*)calloc(image->H, sizeof(float));
		}
	}
	for (i = 0; i < image->H; i++)
	{
		for (j = 0; j< image->W; j++)
		{
			for (k = 0; k < image->C; k++)
			{
				for (m = 0; m < filters[filterindex]->H; m++)
				{
					for (n = 0; n < filters[filterindex]->W; n++)
					{
						(image->data[k][j][i]) += (*images)[imageindex]->data[k][j + m][i + n] * (filters[filterindex]->data[0][m][n]);

					}
				}
			}
		}
	}
	(*cnt)++;
	(*images) = (CUBIC **)realloc((*images), (*cnt) * sizeof(CUBIC*));
	(*images)[(*cnt) - 1] = image;
}