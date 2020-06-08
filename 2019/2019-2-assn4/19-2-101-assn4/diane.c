#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	char name[30];
	int** r, ** g, ** b;
	int height, width, ssd_r_ver, ssd_r_horiz, ssd_g_ver, ssd_g_horiz;
	double ssd_r, ssd_g, ncc;
} img;

void make_array(img* image);
void remove_array(img* image);
void get_menu(int* menu, int prev, img* image);
void load_image(img* image, int load);
void calc_SSD(img* image, int ver, int horiz);
//int find_min(img* image, double temp_r, double temp_g);
void print_array(img* image);

int main()
{
	img image;
	int menu; //�޴��� �Է¹޴� ����
	int load = 0; //�̹����� �ҷ��Դ����� Ȯ���ϱ� ���� ����'
	int i, j;

	while (1) {
		get_menu(&menu, load, &image);
		if (menu == 1) {
			load_image(&image, load);
			load = 1;
			//print_array(&image);
		}
		else if (menu == 2) {
			for (i = -15; i < 16; i++) {
				for (j = -15; j < 16; j++) {
					calc_SSD(&image, i, j);
				}
			}
			printf("red: %d %d %lf\n", image.ssd_r_ver, image.ssd_r_horiz, image.ssd_r);
			printf("green: %d %d %lf\n", image.ssd_g_ver, image.ssd_g_horiz, image.ssd_g);
		}
		else if (menu == 3) {

		}
		else if (menu == 4) {
			remove_array(&image);
			break;
		}
	}
	return 0;
}

void make_array(img* image)
{
	int i;
	image->r = (int**)malloc(image->height * sizeof(int*));
	for (i = 0; i < image->height; i++) {
		image->r[i] = (int*)malloc(image->width * sizeof(int));
	}
	image->g = (int**)malloc(image->height * sizeof(int*));
	for (i = 0; i < image->height; i++) {
		image->g[i] = (int*)malloc(image->width * sizeof(int));
	}
	image->b = (int**)malloc(image->height * sizeof(int*));
	for (i = 0; i < image->height; i++) {
		image->b[i] = (int*)malloc(image->width * sizeof(int));
	}
}

void remove_array(img* image)
{
	int i;
	for (i = 0; i < image->height; i++)
		free(image->r[i]);
	free(image->r);
	for (i = 0; i < image->height; i++)
		free(image->g[i]);
	free(image->g);
	for (i = 0; i < image->height; i++)
		free(image->b[i]);
	free(image->b);
}

void get_menu(int* menu, int prev, img* image) //����ڷκ��� menu ��ȣ�� �Է¹޴� �Լ�
{
	if (prev != 1) {
		printf("======================\n");
		printf("[1] �̹��� �ҷ�����\n");
		printf("[2] �̹��� ����(SSD)\n");
		printf("[3] �̹��� ����(NCC)\n");
		printf("[4] ����\n");
		printf("======================\n");
		printf("�޴� ����> ");
		scanf("%d", menu);
		while (1) {//�߸��� �Է��� ��� �ٽ� �Է��� ����
			if (*menu < 1 || 4 < *menu) {
				printf("WRONG ENTER\n");
				printf("======================\n");
				printf("[1] �̹��� �ҷ�����\n");
				printf("[2] �̹��� ����(SSD)\n");
				printf("[3] �̹��� ����(NCC)\n");
				printf("[4] ����\n");
				printf("======================\n");
				printf("�޴� ����> ");
				scanf("%d", menu);
			}
			else if (*menu == 2 || *menu == 3) {
				printf("OPEN AN IMAGE FIRST\n\n");
				printf("======================\n");
				printf("[1] �̹��� �ҷ�����\n");
				printf("[2] �̹��� ����(SSD)\n");
				printf("[3] �̹��� ����(NCC)\n");
				printf("[4] ����\n");
				printf("======================\n");
				printf("�޴� ����> ");
				scanf("%d", menu);
			}
			else break;
		}
	}
	else {
		printf("======================\n");
		printf("[1] �̹��� ���� - ���� �̹���: %s\n", image->name);
		printf("[2] �̹��� ����(SSD)\n");
		printf("[3] �̹��� ����(NCC)\n");
		printf("[4] ����\n");
		printf("======================\n");
		printf("�޴� ����> ");
		scanf("%d", menu);
	}

}

void load_image(img* image, int load)
{
	FILE* file;
	char a;
	int b, c;
	int i, j;

	if (load == 1)
		remove_array(image);

	printf("�̹��� �̸�:");
	scanf("%s", image->name);
	file = fopen(image->name, "r");
	while (file == NULL) {
		printf("FILE OPEN ERROR\n");
		printf("�̹��� �̸�:");
		scanf("%s", image->name);
		file = fopen(image->name, "r");
	}

	fscanf(file, "%c", &a);
	fscanf(file, "%d", &b);
	fscanf(file, "%d", &image->height);
	fscanf(file, "%d", &image->width);
	fscanf(file, "%d", &c);
	make_array(image);
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			fscanf(file, "%d", &image->r[i][j]);
			fscanf(file, "%d", &image->g[i][j]);
			fscanf(file, "%d", &image->b[i][j]);
		}
	}
	printf("�̹��� �б⸦ �Ϸ��߽��ϴ�.\n");
}

void print_array(img* image)
{
	int i, j;
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			printf("%5d", image->r[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			printf("%5d", image->g[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < image->height; i++) {
		for (j = 0; j < image->width; j++) {
			printf("%5d", image->b[i][j]);
		}
		printf("\n");
	}
}

void calc_SSD(img* image, int ver, int horiz)
{
	int i, j;
	double r = 0;
	double g = 0;
	long long int sum_r = 0;
	long long int sum_g = 0;
	int size;

	size = (image->height - fabs(ver)) * (image->width - fabs(horiz));

	if (ver <= 0 && horiz >= 0) {
		for (i = 0; i < image->height + ver; i++) {
			for (j = 0; j < image->width - horiz; j++) {
				sum_r += (image->b[i - ver][j + horiz] - image->r[i][j]) * (image->b[i - ver][j + horiz] - image->r[i][j]);
				sum_g += (image->b[i - ver][j + horiz] - image->g[i][j]) * (image->b[i - ver][j + horiz] - image->g[i][j]);
			}
		}
		r = (double)sum_r / size;
		if (image->ssd_r >= r) {
			image->ssd_r = r;
			image->ssd_r_ver = ver;
			image->ssd_r_horiz = horiz;
		}
		g = (double)sum_g / size;
		if (image->ssd_g >= g) {
			image->ssd_g = g;
			image->ssd_g_ver = ver;
			image->ssd_g_horiz = horiz;
		}
	}
	else if (ver >= 0 && horiz >= 0) {
		for (i = 0; i < image->height - ver; i++) {
			for (j = 0; j < image->width - horiz; j++) {
				sum_r += (image->b[i][j + horiz] - image->r[i + ver][j]) * (image->b[i][j + horiz] - image->r[i + ver][j]);
				sum_g += (image->b[i][j + horiz] - image->g[i + ver][j]) * (image->b[i][j + horiz] - image->g[i + ver][j]);
			}
		}
		r = (double)sum_r / size;
		if (image->ssd_r >= r) {
			image->ssd_r = r;
			image->ssd_r_ver = ver;
			image->ssd_r_horiz = horiz;
		}
		g = (double)sum_g / size;
		if (image->ssd_g >= g) {
			image->ssd_g = g;
			image->ssd_g_ver = ver;
			image->ssd_g_horiz = horiz;
		}
	}
	else if (ver >= 0 && horiz <= 0) {
		for (i = 0; i < image->height - ver; i++) {
			for (j = 0; j < image->width + horiz; j++) {
				sum_r += (image->b[i][j] - image->r[i + ver][j - horiz]) * (image->b[i][j] - image->r[i + ver][j - horiz]);
				sum_g += (image->b[i][j] - image->g[i + ver][j - horiz]) * (image->b[i][j] - image->g[i + ver][j - horiz]);
			}
		}
		r = (double)sum_r / size;
		if (image->ssd_r >= r) {
			image->ssd_r = r;
			image->ssd_r_ver = ver;
			image->ssd_r_horiz = horiz;
		}
		g = (double)sum_g / size;
		if (image->ssd_g >= g) {
			image->ssd_g = g;
			image->ssd_g_ver = ver;
			image->ssd_g_horiz = horiz;
		}
	}
	else if (ver <= 0 && horiz <= 0) {
		for (i = 0; i < image->height + ver; i++) {
			for (j = 0; j < image->width + horiz; j++) {
				sum_r += (image->b[i - ver][j] - image->r[i][j - horiz]) * (image->b[i - ver][j] - image->r[i][j - horiz]);
				sum_g += (image->b[i - ver][j] - image->g[i][j - horiz]) * (image->b[i - ver][j] - image->g[i][j - horiz]);
			}
		}
		r = (double)sum_r / size;
		if (ver == -15 && horiz == -15) {
			image->ssd_r = r;
			image->ssd_r_ver = ver;
			image->ssd_r_horiz = horiz;
		}
		else if (image->ssd_r >= r) {
			image->ssd_r = r;
			image->ssd_r_ver = ver;
			image->ssd_r_horiz = horiz;
		}
		g = (double)sum_g / size;
		if (ver == -15 && horiz == -15) {
			image->ssd_g = g;
			image->ssd_g_ver = ver;
			image->ssd_g_horiz = horiz;
		}
		else if (image->ssd_g >= g) {
			image->ssd_g = g;
			image->ssd_g_ver = ver;
			image->ssd_g_horiz = horiz;
		}
	}
}