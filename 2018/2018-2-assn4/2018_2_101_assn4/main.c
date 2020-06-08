#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FFLUSH while(getchar() != '\n');

typedef struct Cubic {
	char name[100];		// File name
	float*** data;		// Pixel for CUBIC data
	int C, H, W;		// C: channel, H: height, W: width
	int is_normalized;	// Whether image is normalized or not
} CUBIC;

enum { NORMALIZE = 1, DENORMALIZE = 0 };

int main_menu();

int get_num_with_handler(const char* msg, int upperbound);

void cubic_load(CUBIC*** cubics, int* num_cubics, const char* c_type);
void cubic_remove(CUBIC*** cubics, int* num_cubics, const char* c_type);
void image_save(CUBIC** images, int num_img);

void print_all(CUBIC** images, CUBIC** filters, int num_img, int num_ftr);
void print_cubics(CUBIC** cubics, int num_cubics);

void do_normalize(CUBIC** images, int num_img, int flag);
void normalize(CUBIC* image);
void denormalize(CUBIC* image);
void convolution(CUBIC*** images, CUBIC** filters, int* num_img, int num_ftr);

void free_cubic(CUBIC* c);
void free_cubics(CUBIC** images, CUBIC** filters, int num_img, int num_ftr);

int main() {
	CUBIC **images = NULL;
	CUBIC **filters = NULL;
	int num_images = 0, num_filters = 0;

	while (1) {
		switch (main_menu()) {
		case 1: cubic_load(&images, &num_images, "image"); break;
		case 2: image_save(images, num_images); break;
		case 3: cubic_remove(&images, &num_images, "image"); break;
		case 4: cubic_load(&filters, &num_filters, "filter"); break;
		case 5: cubic_remove(&filters, &num_filters, "filter"); break;
		case 6: print_all(images, filters, num_images, num_filters); break;
		case 7: do_normalize(images, num_images, NORMALIZE); break;
		case 8: do_normalize(images, num_images, DENORMALIZE); break;
		case 9: convolution(&images, filters, &num_images, num_filters); break;
		case 10: 
			printf("Thank you for choosing Luke's Image Processor! :D\n");
			free_cubics(images, filters, num_images, num_filters);
			return 0;
		default:
			printf("\n** FATAL ERROR: Unexpected Input\n");
			printf("Check the function returning the menu selection.\n");
			exit(1);
		}
		printf("Successful! Press Enter to continue . . ."); FFLUSH;
	}


}

int main_menu() {
	char input[10] = { '\0' };
	int selection;

	system("cls");

	printf("=============================\n");
	printf("|      WELCOME TO LUKE'S    |\n");
	printf("|      IMAGE CONVOLUTION    |\n");
	printf("|  1. Image load            |\n");
	printf("|  2. Image save            |\n");
	printf("|  3. Inage remove          |\n");
	printf("|  4. Filter load           |\n");
	printf("|  5. Filter remove         |\n");
	printf("|  6. Print                 |\n");
	printf("|  7. Normalize             |\n");
	printf("|  8. Denormalize           |\n");
	printf("|  9. Image convolution     |\n");
	printf("| 10. Quit                  |\n");
	printf("=============================\n");
	
	while (1) {
		printf("Enter number: ");
		scanf("%s", input); FFLUSH;
		selection = atoi(input);
		if (selection < 1 || selection > 10)
			printf("\n*** Invalid Input ***\n");
		else
			return selection;
	}
	
}

int get_num_with_handler(const char* msg, int upperbound) {
	char num[10];
	int valid_num;

	if (upperbound == 0) {
		printf("** There's yet no data to choose\n");
		return -1;
	}

	printf("%s", msg);
	scanf("%s", num); FFLUSH;
	
	if (strcmp(num, "0") == 0)
		valid_num = 0;
	else {
		valid_num = atoi(num);
		if (valid_num == 0) valid_num = -1;
	}

	if (valid_num < 0 || valid_num >= upperbound) {
		printf("\n*** Invalid Input ***\n");
		return -1;
	}
	return valid_num;
}

void cubic_load(CUBIC*** images, int* num_cubics, const char* c_type) {
	int capitalize[20];
	
	char filename[105];
	int len;	// length of the string filename
	
	char p;		// start of the image file text is 'P'
	int c, h, w, range;  // channel, height, width, index range of the image
	int data;	// data of the image pixels
	
	int i, j, k;	// loop variables

	FILE* inf;
	CUBIC* newcubic;

	printf("Enter %s filename: ", c_type);
	scanf("%s", filename); FFLUSH;
	inf = fopen(filename, "r");
	if (inf == NULL) {
		printf("No matching %s found...\n", c_type);
		return;
	}
	fscanf(inf, "%c", &p);
	if (p != 'P') {
		strcpy(capitalize, c_type);
		capitalize[0] += ('A' - 'a');
		printf("** %s with unsupported format...\n", capitalize);
		return;
	}

	newcubic = (CUBIC*)malloc(sizeof(CUBIC));
	newcubic->is_normalized = 0;

	len = strlen(filename);
	for (i = 0; i < len; i++)
		if (filename[i] == '.')
			break;
	for (i = i; i < len; i++)
		filename[i] = '\0';
	strcpy(newcubic->name, filename);

	fscanf(inf, "%d %d %d %d", &c, &w, &h, &range);
	newcubic->C = c;
	newcubic->W = w;
	newcubic->H = h;
	
	newcubic->data = (float***)malloc(c * sizeof(float**));
	for (i = 0; i < c; i++) {
		newcubic->data[i] = (float**)malloc(h * sizeof(float*));
		for (j = 0; j < h; j++)
			newcubic->data[i][j] = (float*)malloc(w * sizeof(float));
	}

	for (i = 0; i < h; i++) 
		for (j = 0; j < w; j++) 
			for (k = 0; k < c; k++) {
				fscanf(inf, "%f", &newcubic->data[k][i][j]);
			}
	fclose(inf);

	*num_cubics = *num_cubics + 1;
	*images = (CUBIC**)realloc(*images, (*num_cubics) * sizeof(CUBIC*));
	(*images)[*num_cubics - 1] = newcubic;

}

void cubic_remove(CUBIC*** cubics, int* num_cubics, const char* c_type) {
	int idx;

	int i;
	char msg[100];

	print_cubics(*cubics, *num_cubics);
	sprintf(msg, "Enter the number of %s to remove: ", c_type);
	idx = get_num_with_handler(msg, *num_cubics);
	if (idx == -1) return;

	free_cubic((*cubics)[idx]);
	
	for (i = idx; i < *num_cubics - 1; i++)
		(*cubics)[i] = (*cubics)[i + 1];

	*num_cubics = *num_cubics - 1;
	*cubics = (CUBIC**)realloc(*cubics, (*num_cubics) * sizeof(CUBIC*));
}

void image_save(CUBIC** images, int num_img) {
	char filename[100];
	int idx;

	FILE* outf;
	int c, w, h;
	int i, j, k;
	int saturated;

	print_cubics(images, num_img);
	idx = get_num_with_handler("Enter the number of image to save: ", num_img);
	if (idx == -1) return;

	if (images[idx]->is_normalized == 1) {
		printf("** Cannot save the normalized image\n");
		return;
	}

	printf("Enter filename for save image: ");
	scanf("%s", filename); FFLUSH;

	outf = fopen(filename, "w");
	if (outf == NULL) {
		printf("** FATAL ERROR : cannot write new file\n");
		exit(1);
	}

	c = images[idx]->C;
	w = images[idx]->W;
	h = images[idx]->H;

	fprintf(outf, "%c%d %d %d %d\n", 'P', c, w, h, 255);


	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
			for (k = 0; k < c; k++) {
				saturated = (int)images[idx]->data[k][i][j];
				if (saturated > 255) saturated = 255;
				else if (saturated < 0) saturated = 0;
				fprintf(outf, "%d ", saturated);
			}
	fclose(outf);
}

void print_all(CUBIC** images, CUBIC** filters, int num_img, int num_ftr)
{
	int i;

	printf("========= IMAGE LIST ========\n");
	print_cubics(images, num_img);

	printf("========= FILTER LIST =======\n");
	print_cubics(filters, num_ftr);
}

void print_cubics(CUBIC** cubics, int num_cubics) {
	int i;
	for (i = 0; i < num_cubics; i++) {
		printf("%d. %s [H: %d, W: %d, C:%d]",
			i, cubics[i]->name,
			cubics[i]->H, cubics[i]->W, cubics[i]->C);
		if (cubics[i]->is_normalized)
			printf(" - nomalized");
		printf("\n");
	}
}

void do_normalize(CUBIC** images, int num_img, int flag) {
	char operation[13];
	int idx;

	int i, j, k;
	char msg[100];

	if (flag == NORMALIZE) strcpy(operation, "normalize");
	else strcpy(operation, "denormalize");

	print_cubics(images, num_img);
	//print_only_cubics(images, num_img, !flag);
	sprintf(msg, "Enter the number of image to %s: ", operation);
	idx = get_num_with_handler(msg, num_img);
	if (idx == -1) return;

	if (images[idx]->is_normalized == flag) {
		printf("** The image is already %sd\n", operation);
		return;
	}

	if (flag == NORMALIZE) normalize(images[idx]);
	else denormalize(images[idx]);

}

void normalize(CUBIC* image) {
	int i, j, k;
	for (k = 0; k < image->C; k++)
		for (i = 0; i < image->H; i++)
			for (j = 0; j < image->W; j++)
				image->data[k][i][j] = image->data[k][i][j] / 128 - 1;
	image->is_normalized = 1;
}

void denormalize(CUBIC* image) {
	int i, j, k;
	for (k = 0; k < image->C; k++)
		for (i = 0; i < image->H; i++)
			for (j = 0; j < image->W; j++)
				image->data[k][i][j] = (image->data[k][i][j] + 1) * 128;
	image->is_normalized = 0;
}

void convolution(CUBIC*** images, CUBIC** filters, int* num_img, int num_ftr) {
	int idx_img, idx_ftr;
	CUBIC* newimage;
	char newname[100];

	int i, j, k, m, n;
	float summation;

	print_cubics(*images, *num_img);
	idx_img = get_num_with_handler("Enter the number of image to convolve: ", *num_img);
	if (idx_img == -1) return;

	print_cubics(filters, num_ftr);
	idx_ftr = get_num_with_handler("Enter the number of filter to convolve: ", num_ftr);
	if (idx_ftr == -1) return;

	newimage = (CUBIC*)malloc(sizeof(CUBIC));
	newimage->is_normalized = (*images)[idx_img]->is_normalized;

	newimage->C = (*images)[idx_img]->C;
	newimage->H = (*images)[idx_img]->H - filters[idx_ftr]->H + 1;
	newimage->W = (*images)[idx_img]->W - filters[idx_ftr]->W + 1;
	
	sprintf(newname, "%s_%s.ppm", (*images)[idx_img]->name, filters[idx_ftr]->name);
	strcpy(newimage->name, newname);

	newimage->data = (float***)malloc(newimage->C * sizeof(float**));
	for (i = 0; i < newimage->C; i++) {
		newimage->data[i] = (float**)malloc(newimage->H * sizeof(float*));
		for (j = 0; j < newimage->H; j++)
			newimage->data[i][j] = (float*)malloc(newimage->W * sizeof(float));
	}

	for (k = 0; k < newimage->C; k++)
		for (i = 0; i < newimage->H; i++)
			for (j = 0; j < newimage->W; j++) {
				summation = 0.0;
				for (m = 0; m < filters[idx_ftr]->H; m++)
					for (n = 0; n < filters[idx_ftr]->W; n++) {
						summation +=
							(*images)[idx_img]->data[k][i + m][j + n]
							* filters[idx_ftr]->data[0][m][n];
					}
				newimage->data[k][i][j] = summation;
			}
	*num_img = *num_img + 1;
	*images = (CUBIC**)realloc(*images, *num_img * sizeof(CUBIC*));
	(*images)[*num_img - 1] = newimage;
}

void free_cubics(CUBIC** images, CUBIC** filters, int num_images, int num_filters) {
	int k;

	for (k = 0; k < num_images; k++)
		free_cubic(images[k]);

	for (k = 0; k < num_filters; k++)
		free_cubic(filters[k]);

	if (num_images > 0) free(images);
	if (num_filters > 0) free(filters);
}

void free_cubic(CUBIC* c) {
	int i, j;

	for (i = 0; i < c->C; i++) {
		for (j = 0; j < c->H; j++)
			free(c->data[i][j]);
		free(c->data[i]);
	}
	free(c->data);
	free(c);
}