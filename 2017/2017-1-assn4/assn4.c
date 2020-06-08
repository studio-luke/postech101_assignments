/*	�� ���α׷��� �̹����� ���õ� �Ϸ��� ���
	(�̹��� �ε�, �̹��� ���, �̹��� ����, �̹��� ��� ��)�� �����Ѵ�.
		�ۼ���: �����
		��¥: 2017-05-14
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<Windows.h>

#define ERROR		printf("�Է°��� ��ȿ���� �ʽ��ϴ�.\n"); return;
#define IMG_DIR		"images/"
#define MAX_LOAD_IMG_SIZE 10

typedef struct
{
	int width; // �̹����� ����
	int height; // �̹����� ����
	int compFlag; // ������ �Ͽ��°� 0: No, 1: Yes
	char *imgName; // �̹����� �̸�
	int **imgValue; // �̹����� �ȼ� ����
} IMGMAT;

// �Լ� ����

void print_menu(void);
int check_input(char* indexchar, int* index, int indexNum);
void _1_view_list(IMGMAT* imageList[], int indexNumber);
int _2_load_image(IMGMAT* imageList[], int index);
void release_compression(IMGMAT* imageList[], FILE* image, int index);
void _3_do_print(IMGMAT* imageList[], int indexNumber);
void print_image(IMGMAT* imageList[], int index);
int _4_remove_image(IMGMAT* imageList[], int indexNumber);
void _5_do_compress(IMGMAT* imageList[], int indexNumber);
void compress_image(IMGMAT* imageList[], FILE* img_c, int index);
void _6_reduce_image(IMGMAT* imageList[], int indexNumber);
int find_mode(int compFlag, int value[], int freq[]);
void _0_free_memory(IMGMAT* imageList[], int indexNumber);

int main()
{
	//system("mode con:cols=170 lines=95");  //  �ܼ� â ũ�� ����
	
	char order[20];  //  order : �޴� ��ɾ �޴� ����
	int index = 0;  //  index : �ε�� �̹����� ������ �����ϴ� ����
	IMGMAT *image[MAX_LOAD_IMG_SIZE];

	while (1) {
		print_menu();
		fgets(order, 20, stdin);

		if (order[1] != '\n') {
			printf("�Է��� ��ȣ�� �ش�Ǵ� �޴��� �����ϴ�.\n");
			continue;
		}  //  �Է��� �� ���ڷ� ����
		
		switch (order[0]) {
		case '1':
			_1_view_list(image, index);
			break;
		case '2':
			index = _2_load_image(image, index);
			break;
		case '3':
			_3_do_print(image, index);
			break;
		case '4':
			if (_4_remove_image(image, index) == 0)
				index--;
			break;
		case '5':
			_5_do_compress(image, index);
			break;
		case '6':
			_6_reduce_image(image, index);
			break;
		case '0':
			_0_free_memory(image, index);
			return 0;
		default:
			printf("�Է��� ��ȣ�� �ش�Ǵ� �޴��� �����ϴ�.\n");
			break; // 1, 2, 3, 4, 5, 6, 0 ���� �Է��� ��� ���� ó��
		}  //  switch
	}  //  while

}  //  main

/*	============================== print_menu ==============================
	����ڿ��� ���α׷��� �����ϴ� �� �ʿ��� �޴��� ����Ѵ�.
	Pre		����
	Post	�޴� ���
*/

void print_menu(void)
{
	printf("========================================\n");
	printf("[1] �̹��� ��� ����\n");
	printf("[2] �̹��� �ε�\n");
	printf("[3] �̹��� ���\n");
	printf("[4] �̹��� ����\n");
	printf("[5] �̹��� ����\n");
	printf("[6] �̹��� ���\n");
	printf("[0] ����\n");
	printf("========================================\n");
	printf("�޴� ��ȣ �Է�: ");
}  //  print_menu

/*	============================== _1_view_list ==============================
	1�� �޴��� �ش��ϴ� �������,
	���� �ε�� �̹����� ����� ����Ѵ�.
	Pre		�̹����� �ε�ǰų�, �ε���� ����
	Post	�̹��� ��� �Ǵ� ���� ���
*/

void _1_view_list(IMGMAT* imgList[], int indexNum)
{
	int i;

	if (indexNum == 0) {
		printf("ǥ���� �̹����� �����ϴ�.\n");
		return;
	}  //  indexNum�� �ε�� �̹��� ������ ��Ÿ��.

	for (i = 0; i < indexNum; i++)
		printf("[%d]�� �̹��� �̸�: %s\n", i + 1, imgList[i]->imgName);  // �̹��� ��� ���

	return;
}  //  _1_view_list

/*	============================== _2_load_image ==============================
	2�� �޴��� �ش��ϴ� �������,
	����� �̹��� �ؽ�Ʈ ������ �о�
	�̹����� ���� ������ ����ü ������ �����Ѵ�.
	Pre		�ؽ�Ʈ ������ ������ ������ ����Ǿ� ����
	Post	�̹��� ���� ���� �� �޽��� ���
*/

int _2_load_image(IMGMAT* imgList[], int index)
{
	FILE* image;
	char fileFullName[40] = IMG_DIR;
	char inputName[30];
	int i, j;

	if (index >= MAX_LOAD_IMG_SIZE) {
		printf("�̹����� �� �̻� ���� �� �����ϴ�.\n");
		return index;
	}  //  ������ ���� �̻��� �̹����� �ε��Ϸ� �� �� ���� ���
	
	printf("���� �̹��� �̸�: ");
	fgets(inputName, 30, stdin);
	inputName[strcspn(inputName, "\n")] = 0;
	strcat(fileFullName, inputName);

	if ((image = fopen(fileFullName, "r")) == NULL) {
		printf("�̹����� ã�� �� �����ϴ�.\n");
		return index;
	}  //  �Է��� �̸��� ������ ã�� �� ���� ��� ���� ���

	for (i = 0; i < index; i++)
		if (strcmp(inputName, imgList[i]->imgName) == 0) {
			printf("�̹� ���� �����Դϴ�.\n");
			return index;
		}   //  ������� �ε�� ���ϵ�� ���Ͽ�
			//  ������ �̸��� ������ ���� ��� �ߺ� �ε� ����

	imgList[index] = malloc(sizeof(IMGMAT)); // ����ü�� �޸� �Ҵ�
	fscanf(image, "%d%d%d", &imgList[index]->height,
		&imgList[index]->width, &imgList[index]->compFlag);

	imgList[index]->imgName = malloc((strlen(inputName) + 1) * sizeof(char));  
	imgList[index]->imgValue = malloc(imgList[index]->height * sizeof(int*)); // int** �� �޸� �Ҵ�
	for (i = 0; i < imgList[index]->height; i++)
		imgList[index]->imgValue[i] = malloc(imgList[index]->width * sizeof(int)); // int* �� �޸� �Ҵ�
	
	strcpy(imgList[index]->imgName, inputName);
	if (imgList[index]->compFlag == 0)
		for (i = 0; i < imgList[index]->height; i++)
			for (j = 0; j < imgList[index]->width; j++)
				fscanf(image, "%d", *(imgList[index]->imgValue + i) + j);  //  ������� ���� ������ ���
																		   //  ���ʴ�� �о� ����
	else {
		release_compression(imgList, image, index);
	}
	
	fclose(image);
	printf("[%s]�� ���������� �ε��Ͽ����ϴ�.\n", inputName);
	
	return ++index;  //  �ε�� �̹��� ���� ����
}  //  _2_load_image

/*	============================== release_compression ==============================
	�̹����� �ε��� ��, ����Ǿ� �ִ� ������ �ؼ��Ͽ�
	���� �ε��� ���� ����ü�� �ε��ϴ� �Լ�
	Pre		�ؽ�Ʈ ���� ���� ����
	Post	�̹��� ���� �ε��� ����
*/

void release_compression(IMGMAT* imgList[], FILE* image, int index)
{
	int colorIndex, indexNumber;
	int linearIndex = 0, row, col; //  linearIndex : 1�� �����ϸ� ����ü�� row�� col�� �����ϴ� ����
								   //  row�� col�� ���� �ε����� ������ ������ �迭�� ���Ҹ� ����
	int i;

	while (linearIndex < imgList[index]->height * imgList[index]->width) {
		fscanf(image, "%d", &colorIndex);
		fscanf(image, "%d", &indexNumber);
		for (i = 0; i < indexNumber; i++) {
			row = linearIndex / imgList[index]->width;
			col = linearIndex - row * imgList[index]->width; // ������ �������� Ȱ���Ͽ� row, col ����
			imgList[index]->imgValue[row][col] = colorIndex;
			linearIndex++;
		}
	}
	return;
}  //  release_compression

/*	============================== check_input ==============================
	����ڰ� ���α׷� ��� �� �̹��� ��ȣ�� �Է����� ��,
	�ε�� �̹��� ������ �ٰ��Ͽ� �Է��� ��ȣ�� �ش��ϴ� �̹����� �����ϴ���
	�Ǵ��ϴ� �Լ�
	Pre		����ڷκ��� �̹��� ��ȣ �Է��� ����
	Post	���ڸ� ���� ������ ��ȯ (Ȥ�� ���� ���)
*/

int check_input(char *indexchar, int *index, int indexNum)
{
	if (indexchar[1] == '\n') 
		*index = indexchar[0] - '0';  //  �Է°��� �� �ڸ���� �� ���� ���ڷ� ��ȯ
	else if ('0' <= indexchar[1] && indexchar[1] <= '9' && indexchar[2] == '\n')
		*index = (indexchar[0] - '0') * 10 + indexchar[1] - '0'; //  �Է°��� �� �ڸ���� �� ���� ���ڷ� ��ȯ
	else {
		ERROR 1;  //  �� �ܿ��� ��� ���� ó��
	}

	if (*index <= 0 || *index > indexNum) {
		ERROR 1;  //  �ε����� �ش��ϴ� �̹����� ���� �� ���� ó��
	}
	return 0;
}  //  check_input

/*	============================== _3_do_print ==============================
	����ڷκ��� ����� �̹��� ��ȣ�� �Է¹ް�, ��� �Լ��� ȣ���Ѵ�.
	Pre		�̹��� �ε� Ȥ�� ����
	Post	�̹��� ��� Ȥ�� ���� ���
*/

void _3_do_print(IMGMAT* imgList[], int indexNum)
{
	char printWhat[20];
	char* startIndexchar, * endIndexchar;
	int startIndex = 0, endIndex = 0;
	int i;

	printf("����� �̹��� ��ȣ�� ����: ");
	fgets(printWhat, 20, stdin);
	printWhat[strcspn(printWhat, "\n")] = 0;

	if (strlen(printWhat) == 0 || printWhat[0] == '-') {
		ERROR;
	}  //  strtok �Լ��� ����ϱ� �� '-'�� ���ڿ��� �����ϴ� ��츦 �����Ѵ�.
	   //  "-2-3" ���� �Է��� ������ �����ϱ� ���ؼ��̴�.

	startIndexchar = strtok(printWhat, "-");
	endIndexchar = strtok(NULL, "");  //  '-'�� ���� ���ĸ� ����

	for (i = 0; i < strlen(startIndexchar); i++) {
		if (startIndexchar[i] < '0' || startIndexchar[i] > '9') {
			ERROR;
		}  //  startIndexchar�� ���̸�ŭ for���� ������ ���ڰ� �ƴ� ���� �߰ߵǴ� ��� ���� ó��
		startIndex += (startIndexchar[i] - '0') * pow(10, strlen(startIndexchar) - 1 - i);
	}  //  ���ڿ��� ���ڸ����� �̷���������� �̸� �������� �ٲپ� �����Ѵ�.
	
	if (endIndexchar == NULL) {  //  ������ �ƴ� �ϳ��� ���ڸ� �Է��Ͽ� endIndexchar�� null pointer�� ��
		if (startIndex <= 0 || startIndex > indexNum) {
			ERROR;
		}  //  �Է°��� �ش��ϴ� �̹����� ���� �ÿ� ���� ���
		print_image(imgList, startIndex - 1);
	}
	else {
		for (i = 0; i < strlen(endIndexchar); i++) {
			if (endIndexchar[i] < '0' && endIndexchar[i] > '9') {
				ERROR;
			} //  endIndexchar�� ���̸�ŭ for���� ������ ���ڰ� �ƴ� ���� �߰ߵǴ� ��� ���� ó��
			endIndex += (endIndexchar[i] - '0') * pow(10, strlen(endIndexchar) - 1 - i);
		}  //  ���ڿ��� ���ڸ����� �̷���������� �̸� �������� �ٲپ� �����Ѵ�.
		
		if (startIndex <= 0 || endIndex > indexNum || endIndex < startIndex) {
			ERROR;
		}  //  �Է°��� ��ȿ���� ���� ��� ���� ó��
		for (i = startIndex; i <= endIndex; i++)
			print_image(imgList, i - 1);
	}
	return;
}  //  _3_do_print

/*	============================== print_image ==============================
	���� �ε����� �̿��Ͽ� ������ �̹����� ����ϴ� �Լ�.
	���� ó�� �������� �̹��� ��� ����� ���� �������� ������ �Ǿ�
	�Լ��� ���� ����� �Ǿ���.
	Pre		����� �̹��� ��ȣ ����
	Post	�̹��� ���
*/

void print_image(IMGMAT* imgList[], int index)
{
	int i, j;
	
	for (i = 0; i < imgList[index]->height; i++) {
		for (j = 0; j < imgList[index]->width; j++) {
			if (imgList[index]->compFlag == 0)
				//  ����� ������ ���� ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), imgList[index]->imgValue[i][j] / 10);
			else
				//  ����� ������ �����ε����� �̹� ����ȭ�� �����̱⿡ 10���� ������ �ʵ��� �Ѵ�
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), imgList[index]->imgValue[i][j]);
			printf("��");
		}
		printf("\n");
	}
	//  ���ڻ� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n");
}  //  print_image

/*	============================== _4_remove_image ==============================
	�ε�� �̹����� �����ϰ�, �̹��� �ε����� �ϳ��� ���� �մ���
	Pre		�̹��� �ε� Ȥ�� ����
	Post	�ε�� �̹��� ���� Ȥ�� ����
*/

int _4_remove_image(IMGMAT* imgList[], int indexNum)
{
	char indexchar[20];
	int index;
	int i, j;

	printf("������ �̹��� ��ȣ: ");
	fgets(indexchar, 20, stdin);
	
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  �߸��� �Է¿� ���� ���� ó��

	for (; index < indexNum; index++) {
		imgList[index - 1]->imgName = realloc(imgList[index - 1]->imgName, (strlen(imgList[index]->imgName) + 1) * sizeof(char));
		free(imgList[index - 1]->imgValue);  // �̸� �޸� ���Ҵ� �� �����
		imgList[index - 1]->imgValue = calloc(imgList[index]->height, sizeof(int*));
		for (int i = 0; i < imgList[index]->height; i++)
			imgList[index - 1]->imgValue[i] = realloc(imgList[index - 1]->imgValue[i], imgList[index]->width * sizeof(int));
		for (i = 0; i < imgList[index]->height; i++)
			for (j = 0; j < imgList[index]->width; j++)
				*(*(imgList[index - 1]->imgValue + i) + j) = *(*(imgList[index]->imgValue + i) + j); //  ���� �ε��� �޸� ���Ҵ� �� �����
		imgList[index - 1]->height = imgList[index]->height;
		imgList[index - 1]->width = imgList[index]->width;
		imgList[index - 1]->compFlag = imgList[index]->compFlag;
		strcpy(imgList[index - 1]->imgName, imgList[index]->imgName);  //  ��Ÿ �̹��� ���� �����
	}
	if (index == indexNum) {  
		free(imgList[index - 1]->imgName);
		for (i = 0; i < imgList[index - 1]->height; i++)
			free(imgList[index - 1]->imgValue[i]);
		free(imgList[index - 1]->imgValue);
		free(imgList[index - 1]);
	}  //  ������ ��ȣ�� �̹����� �����ϸ� �޸𸮸� �����Ѵ�
	printf("���������� �����Ͽ����ϴ�.\n");
	return 0;
}

/*	============================== _5_do_compress ==============================
	����ڷκ��� ������ �̹��� ��ȣ�� �Է¹޾�
	����� �̹��� �ؽ�Ʈ ������ �����Ѵ�
	Pre		�̹��� �ε� �Ǵ� ����
	Post	����� �̹��� �ؽ�Ʈ ���� ���� �Ǵ� ����
*/

void _5_do_compress(IMGMAT* imgList[], int indexNum)
{
	char indexchar[20], newFileName[32], fileFullName[40] = IMG_DIR;
	int index, cmp1, cmp2, colorIndexNum = 1;
	int i, j;
	FILE *img_c;

	printf("������ �̹��� ��ȣ: ");
	fgets(indexchar, 20, stdin);
	
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  ��ȿ���� ���� �Է¿� ���� ���� ó��
	
	if (imgList[index - 1]->compFlag == 1) {
		printf("�̹� ������ �����Դϴ�.\n");
		return 1;
	}  //  �̹� ����� ���� �ߺ� ���� ����

	strcpy(newFileName, imgList[index - 1]->imgName);
	newFileName[strlen(newFileName) - 4] = '\0';  //  '.txt'�� ����� ���� '.' ��ġ�� null ���� ����
	strcat(newFileName, "_c.txt");  //  �̹��� �̸� �ڿ� '_c.txt' �̾���̱�

	strcat(fileFullName, newFileName);
	if ((img_c = fopen(fileFullName, "w")) == NULL)
		printf("[%s]�� ������ �� �����ϴ�.\n", newFileName);
	
	fprintf(img_c, "%d %d 1\n", imgList[index - 1]->height, imgList[index - 1]->width);
	compress_image(imgList, img_c, index);

	fclose(img_c);
	printf("���������� �����Ͽ����ϴ�. �������ϸ�: [%s]\n", newFileName);
	
	return 0;
}  // _5_do_compress_image

/*	============================== compress_image ==============================
	������ ������ �����Ѵ�.
	�Ŀ� �̹��� ��� �Լ������� ������ ����� ���� �־�
	�Լ��� ���� �����Ͽ���.
	Pre		������ �̹��� ��ȣ �Է¹���, �����ų �̹��� �ؽ�Ʈ ���� ����
	Post	����� �̹��� �ؽ�Ʈ ���� ����
*/

void compress_image(IMGMAT* imgList[], FILE* img_c, int index)
{
	int cmp1, cmp2, colorIndexNum = 1;
	int i, j;

	cmp1 = imgList[index - 1]->imgValue[0][0] / 10;
	for (i = 0; i < imgList[index - 1]->height; i++)
		for (j = 0; j < imgList[index - 1]->width; j++) {
			if (i == 0 && j == 0)
				continue; //  ó���� cmp1�� ���� �� �� �����Ͽ����Ƿ� �ݺ����� �� �� �����Ѵ�
			cmp2 = imgList[index - 1]->imgValue[i][j] / 10;
			if (cmp1 == cmp2)
				colorIndexNum++;  //  ���������� �̹��� ������ ������ ���� �����ε����� �ݺ��Ǵ� ���� ����
			else {
				fprintf(img_c, "%d %d ", cmp1, colorIndexNum);
				colorIndexNum = 1;
				cmp1 = cmp2;
			}  //  �����ε������� �޶����� �������� �������� �ݺ��Ǿ� �����ߴ� �����ε����� �ݺ��� Ƚ���� ����Ѵ�.
		}
	fprintf(img_c, "%d %d", cmp2, colorIndexNum);  //  ���ǹ� ������ ���������� �ݺ��� ���� �ε����� ��µ��� �����Ƿ� ����
	return;
}

/*	============================== _6_reduce_image ==============================
	����� �̹��� ��ȣ�� �Է¹ް�, ��ҵ� �̹��� �ؽ�Ʈ ������ �����Ѵ�.
	Pre		�̹��� �ε�� �Ǵ� ����
	Post	��ҵ� �̹��� �ؽ�Ʈ ���� ���� �Ǵ� ����
*/

void _6_reduce_image(IMGMAT* imgList[], int indexNum)
{
	char indexchar[20];
	char newFileName[30];
	char fileFullName[40] = IMG_DIR;
	int index, i, j, k;
	int val[4], freq[4] = { 0 }, mode;
	FILE* img_r;
	IMGMAT* reducedImg[1];

	printf("����� �̹��� ��ȣ: ");
	fgets(indexchar, 20, stdin);
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  ��ȿ���� ���� �Է¿� ���� ���� ó��
	
	if (imgList[index -1]->height / 2 <20 || imgList[index-1]->width / 2 <20) {
		printf("�� �̻� ����� �� �����ϴ�.\n");
		return 1;
	}  //  ���� �Ǵ� ���ΰ� 20 �ȼ� ������ �� ��Ҹ� �������� �ʴ´�

	strcpy(newFileName, imgList[index - 1]->imgName);
	newFileName[strlen(newFileName) - 4] = '\0'; // �̹��� �̸����� ".txt"�� ����� ���� '.' ��ġ�� null ���� ����
	strcat(newFileName, "_r.txt");
	strcat(fileFullName, newFileName);

	if ((img_r = fopen(fileFullName, "w")) == NULL)
		printf("[%s]�� ������ �� �����ϴ�.\n", newFileName);
	
	reducedImg[0] = malloc(sizeof(IMGMAT));
	reducedImg[0]->imgValue = calloc(imgList[index - 1]->height / 2, sizeof(int*));
	for (i = 0; i < imgList[index - 1]->height / 2; i++)
		reducedImg[0]->imgValue[i] = calloc(imgList[index - 1]->width / 2, sizeof(int)); // �ӽ÷� ������ ����ü�� �޸� �Ҵ�

	reducedImg[0]->height = imgList[index - 1]->height / 2;
	reducedImg[0]->width = imgList[index - 1]->width / 2;
	for (i = 0; i < imgList[index - 1]->height - 1; i += 2)
		for (j = 0; j < imgList[index - 1]->width - 1; j += 2) {
			val[0] = imgList[index - 1]->imgValue[i][j];
			val[1] = imgList[index - 1]->imgValue[i][j + 1];
			val[2] = imgList[index - 1]->imgValue[i + 1][j];
			val[3] = imgList[index - 1]->imgValue[i + 1][j + 1];
			// 4���� �ȼ��� �ϳ��� ���̱� ���� �ϳ��� �迭�� ����

			mode = find_mode(imgList[index-1]->compFlag, val, freq);  // �����ε����� �ְ� �� ���� ���
									      // �� ���� �ε����� ���� �󵵸� �迭�� ����
			for (k = 0; k < 4; k++)
				if (freq[k] == mode) {
					reducedImg[0]->imgValue[i / 2][j / 2] = val[k];
					break;
				}  //  �켱���� ������ �˻��Ͽ� �ֺ� �����ε����� �߰ߵǸ� ���� ����
		}
	fprintf(img_r, "%d %d %d\n", reducedImg[0]->height, reducedImg[0]->width, imgList[index-1]->compFlag);
	if (imgList[index - 1]->compFlag == 0) {
		for (i = 0; i < reducedImg[0]->height; i++)
			for (j = 0; j < reducedImg[0]->width; j++)
				fprintf(img_r, "%d ", reducedImg[0]->imgValue[i][j]);
	}
	else {
		for (i = 0; i < reducedImg[0]->height; i++)
			for (j = 0; j < reducedImg[0]->width; j++)
				reducedImg[0]->imgValue[i][j] *= 10; // �����ϴ� �������� �����ε����� ����ȭ�ϴ� ������ �ִµ�,
													 // �̹� ����� ������ �ε��� ��� �����ε����� �̹� ����ȭ �Ǿ������Ƿ� 10�� �����ش�

		compress_image(reducedImg, img_r, 1);
	}  //  ����� ������ ����ϴ� ��� ������ ������ �� �����Ͽ� ����

	for (i = 0; i < imgList[index - 1]->height / 2; i++)
		free(reducedImg[0]->imgValue[i]);
	free(reducedImg[0]->imgValue);  //  �ӽ÷� ������ ����ü �޸� ����

	fclose(img_r);

	printf("���������� ����Ͽ����ϴ�. ������ϸ�: [%s]\n", newFileName);
	return 0;

}  //  _6_reduce_image

/*	============================== find_mode ==============================
	4���� �迭 ���ҵ��� �ִ� �󵵼��� ã��,
	�� ���ҵ��� �󵵼��� �迭�� ����
	Pre		�迭�� ����ȭ�� �����ε����� ����
	Post	��ҵ� �̹��� �ؽ�Ʈ ���� ���� �Ǵ� ����
*/

int find_mode(int compFlag, int val[], int freq[])
{
	int i, j;
	int max;

	for (i = 0; i < 4; i++)
		freq[i] = 0;
	if (compFlag == 0) {
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (val[i] / 10 == val[j] / 10)
					freq[i]++;
	}
	else
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (val[i] / 10 == val[j])
					freq[i]++;

	max = freq[0];
	for (i = 1; i < 4; i++)
		if (freq[i - 1] < freq[i])
			max = freq[i];
	return max;
}

void _0_free_memory(IMGMAT* imgList[], int indexNum)
{
	int i, j;

	for (i = 0; i < indexNum; i++) {
		free(imgList[i]->imgName);
		for (j = 0; j < imgList[i]->height; j++)
			free(imgList[i]->imgValue[j]);
		free(imgList[i]->imgValue);
		free(imgList[i]);
	}
	return;
}