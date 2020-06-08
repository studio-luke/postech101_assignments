#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define FFLUSH while(getchar() != '\n')
#define SQUARE(X) ((X)*(X))
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#define MAX(X, Y) ((X)>(Y)?(X):(Y))

typedef struct {
	int stored;
	char name[30];
	int h, w;
	int** R;
	int** G;
	int** B;
} image;

int print_menu(image* img) {
	int menu;

	while (1) {
		printf("===================\n");
		if (img->stored)
			printf("[1] 이미지 변경 - 현재 이미지: %s\n", img->name);
		else
			printf("[1] 이미지 불러오기\n");
		printf("[2] 이미지 정합(SSD)\n");
		printf("[3] 이미지 정합(NCC)\n");
		printf("[4] 종료\n");
		printf("===================\n");
		printf("메뉴 선택 > ");
		scanf("%d", &menu); FFLUSH;
		if (menu < 1 && 4 < menu) {
			printf("유효하지 않은 입력값입니다.\n");
			continue;
		}
		if ((menu == 2 || menu == 3) && !img->stored) {
			printf("이미지를 불러오세요.\n");
			continue;
		}
		break;
	}

	return menu;

}

void free_img(image* img) {
	int i;
	if (!img->stored)
		return;
	for (i = 0; i < img->h; i++) {
		free(img->R[i]);
		free(img->G[i]);
		free(img->B[i]);
	}
	free(img->R);
	free(img->G);
	free(img->B);
}

void load_image(image* img) {
	FILE* f;
	int dmpi;
	int i, j;
	char dmpc;

	printf("이미지이름: ");
	scanf("%s", img->name);

	if ((f = fopen(img->name, "r")) == NULL) {
		printf("파일(%s)을 열 수 없습니다..", img->name);
		return;
	}

	if (img->stored) {
		free_img(img);
	}

	fscanf(f, "%c%d", &dmpc, &dmpi); // catching 'P3'
	fscanf(f, "%d %d", &img->w, &img->h);
	fscanf(f, "%d", &dmpi);			// catching '255'

	img->R = (int**)malloc(img->h * sizeof(int*));
	img->G = (int**)malloc(img->h * sizeof(int*));
	img->B = (int**)malloc(img->h * sizeof(int*));
	for (i = 0; i < img->h; i++) {
		img->R[i] = (int*)malloc(img->w * sizeof(int));
		img->G[i] = (int*)malloc(img->w * sizeof(int));
		img->B[i] = (int*)malloc(img->w * sizeof(int));
	}

	for (i = 0; i < img->h; i++) {
		for (j = 0; j < img->w; j++) {
			fscanf(f, "%d %d %d", &(img->R[i][j]), &(img->G[i][j]), &(img->B[i][j]));
		}
	}
	
	img->stored = 1;
	printf("이미지 읽기를 완료했습니다.\n");
	fclose(f);
}

int SSD(image* img, int h_diff, int w_diff, double* relRB, double* relGB) {
	int new_h = img->h - abs(h_diff);
	int new_w = img->w - abs(w_diff);
	int i, j;
	int Ri, Gi, Bi, Rj, Gj, Bj;

	int sumRB = 0, sumGB = 0;

	for (i = 0; i < new_h; i++) {
		Ri = Gi = h_diff >= 0 ? i : i - h_diff;
		Bi =	   h_diff < 0 ? i : i + h_diff;
		for (j = 0; j < new_w; j++) {
			Rj = Gj = w_diff >= 0 ? j : j - w_diff;
			Bj =	   w_diff < 0 ? j : j + w_diff;
			sumRB += SQUARE(img->R[Ri][Rj] - img->B[Bi][Bj]);
			sumGB += SQUARE(img->G[Gi][Gj] - img->B[Bi][Bj]);
		}
	}

	*relRB = (double)sumRB / (new_w * new_h);
	*relGB = (double)sumGB / (new_w * new_h);
}

int NCC(image* img, int h_diff, int w_diff, double *relRB, double *relGB) {
	int new_h = img->h - abs(h_diff);
	int new_w = img->w - abs(w_diff);
	int i, j;
	int Ri, Gi, Bi, Rj, Gj, Bj;
	
	long long int sumRBmul, sumGBmul, sumRsqu, sumGsqu, sumBsqu;
	sumRBmul = sumGBmul = sumRsqu = sumGsqu = sumBsqu = 0;

	for (i = 0; i < new_h; i++) {
		Ri = Gi = h_diff >= 0 ? i : i - h_diff;
		Bi =	   h_diff < 0 ? i : i + h_diff;
		for (j = 0; j < new_w; j++) {
			Rj = Gj = w_diff >= 0 ? j : j - w_diff;
			Bj =	   w_diff < 0 ? j : j + w_diff;
			sumRBmul += img->R[Ri][Rj] * img->B[Bi][Bj];
			sumGBmul += img->G[Gi][Gj] * img->B[Bi][Bj];
			sumRsqu  += SQUARE(img->R[Ri][Rj]);
			sumGsqu  += SQUARE(img->G[Gi][Gj]);
			sumBsqu  += SQUARE(img->B[Bi][Bj]);
		}
	}

	*relRB = (double)sumRBmul / sqrt(sumRsqu * sumBsqu);
	*relGB = (double)sumGBmul / sqrt(sumGsqu * sumBsqu);
}

int align(image* img, const char* flag) {
	int h_diff, w_diff;
	int i, j;
	double relRB, relGB;
	double minMaxRB = -INFINITY;
	double minMaxGB = -INFINITY;
	int is_SSD = 0;
	int minRB_h_diff, minRB_w_diff, minGB_h_diff, minGB_w_diff;
	char outname[30];


	if (strcmp(flag, "SSD") == 0) {
		is_SSD = 1;
		minMaxRB = INFINITY;
		minMaxGB = INFINITY;
	}

	for (h_diff = -15; h_diff <= 15; h_diff++) {
		for (w_diff = -15; w_diff <= 15; w_diff++) {
			if (is_SSD) 
				SSD(img, h_diff, w_diff, &relRB, &relGB);	
			else 
				NCC(img, h_diff, w_diff, &relRB, &relGB);

			if (is_SSD ? minMaxRB > relRB : minMaxRB < relRB) {
				minMaxRB = relRB;
				minRB_h_diff = h_diff;
				minRB_w_diff = w_diff;
				printf("%lf, %d, %d\n", minMaxRB, h_diff, w_diff);
			}
			if (is_SSD ? minMaxGB > relGB : minMaxGB < relGB) {
				minMaxGB = relGB;
				minGB_h_diff = h_diff;
				minGB_w_diff = w_diff;
			}
		}
	}

	printf("\n===================\n");
	printf("%s - R: [%d, %d], G: [%d, %d]\n", flag, 
		minRB_w_diff, -minRB_h_diff, minGB_w_diff, -minGB_h_diff);

	// int adjRB_h = img->h - (minRB_h_diff * minRB_w_diff > 0);
	int cut_h_from = MAX(MAX(minRB_h_diff, minGB_h_diff), 0);
	int cut_h_to = img->h + MIN(MIN(minRB_h_diff, minGB_h_diff), 0);
	int cut_w_from = MAX(MAX(minRB_w_diff, minGB_w_diff), 0);
	int cut_w_to = img->w + MIN(MIN(minRB_w_diff, minGB_w_diff), 0);

	img->name[strlen(img->name) - 4] = '\0'; // cut the .ppm
	sprintf(outname, "%s_%s_R%d_%d_G%d_%d.ppm", img->name, flag,
		minRB_w_diff, -minRB_h_diff, minGB_w_diff, -minGB_h_diff);
	img->name[strlen(img->name)] = '.'; 

	FILE* out = fopen(outname, "w");
	fprintf(out, "P3 %d %d 255\n", cut_w_to - cut_w_from, cut_h_to - cut_h_from);
	for (i = cut_h_from; i < cut_h_to; i++) {
		for (j = cut_w_from; j < cut_w_to; j++) {
			fprintf(out, "%d %d %d ", img->R[i-minRB_h_diff][j-minRB_w_diff], 
				img->G[i-minGB_h_diff][j-minGB_w_diff], img->B[i][j]);
		}
	}

	printf("결과 이미지 파일: %s\n", outname); 
	printf("===================\n\n");
	fclose(out);
}


int main() {
	image* img = (image*)malloc(sizeof(image));
	int i;
	int a[10][10];

	img->stored = 0;
	while (1) {
		switch (print_menu(img)) {
		case 1: load_image(img); break;
		case 2:	align(img, "SSD"); break;
		case 3: align(img, "NCC"); break;
		case 4: free_img(img); return 0;
		}
	}
}