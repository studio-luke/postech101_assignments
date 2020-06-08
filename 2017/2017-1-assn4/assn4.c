/*	이 프로그램은 이미지에 관련된 일련의 기능
	(이미지 로드, 이미지 출력, 이미지 압축, 이미지 축소 등)을 수행한다.
		작성자: 김승일
		날짜: 2017-05-14
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<Windows.h>

#define ERROR		printf("입력값이 유효하지 않습니다.\n"); return;
#define IMG_DIR		"images/"
#define MAX_LOAD_IMG_SIZE 10

typedef struct
{
	int width; // 이미지의 넓이
	int height; // 이미지의 높이
	int compFlag; // 압축을 하였는가 0: No, 1: Yes
	char *imgName; // 이미지의 이름
	int **imgValue; // 이미지의 픽셀 값들
} IMGMAT;

// 함수 선언

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
	//system("mode con:cols=170 lines=95");  //  콘솔 창 크기 설정
	
	char order[20];  //  order : 메뉴 명령어를 받는 변수
	int index = 0;  //  index : 로드된 이미지의 개수를 저장하는 변수
	IMGMAT *image[MAX_LOAD_IMG_SIZE];

	while (1) {
		print_menu();
		fgets(order, 20, stdin);

		if (order[1] != '\n') {
			printf("입력한 번호에 해당되는 메뉴가 없습니다.\n");
			continue;
		}  //  입력을 한 글자로 제한
		
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
			printf("입력한 번호에 해당되는 메뉴가 없습니다.\n");
			break; // 1, 2, 3, 4, 5, 6, 0 외의 입력은 모두 에러 처리
		}  //  switch
	}  //  while

}  //  main

/*	============================== print_menu ==============================
	사용자에게 프로그램을 조작하는 데 필요한 메뉴를 출력한다.
	Pre		없음
	Post	메뉴 출력
*/

void print_menu(void)
{
	printf("========================================\n");
	printf("[1] 이미지 목록 보기\n");
	printf("[2] 이미지 로드\n");
	printf("[3] 이미지 출력\n");
	printf("[4] 이미지 제거\n");
	printf("[5] 이미지 압축\n");
	printf("[6] 이미지 축소\n");
	printf("[0] 종료\n");
	printf("========================================\n");
	printf("메뉴 번호 입력: ");
}  //  print_menu

/*	============================== _1_view_list ==============================
	1번 메뉴에 해당하는 기능으로,
	현재 로드된 이미지의 목록을 출력한다.
	Pre		이미지가 로드되거나, 로드되지 않음
	Post	이미지 목록 또는 에러 출력
*/

void _1_view_list(IMGMAT* imgList[], int indexNum)
{
	int i;

	if (indexNum == 0) {
		printf("표시할 이미지가 없습니다.\n");
		return;
	}  //  indexNum은 로드된 이미지 개수를 나타냄.

	for (i = 0; i < indexNum; i++)
		printf("[%d]번 이미지 이름: %s\n", i + 1, imgList[i]->imgName);  // 이미지 목록 출력

	return;
}  //  _1_view_list

/*	============================== _2_load_image ==============================
	2번 메뉴에 해당하는 기능으로,
	저장된 이미지 텍스트 파일을 읽어
	이미지에 대한 정보를 구조체 변수에 저장한다.
	Pre		텍스트 파일이 지정된 폴더에 저장되어 있음
	Post	이미지 정보 저장 및 메시지 출력
*/

int _2_load_image(IMGMAT* imgList[], int index)
{
	FILE* image;
	char fileFullName[40] = IMG_DIR;
	char inputName[30];
	int i, j;

	if (index >= MAX_LOAD_IMG_SIZE) {
		printf("이미지를 더 이상 읽을 수 없습니다.\n");
		return index;
	}  //  지정된 개수 이상의 이미지를 로드하려 할 때 에러 출력
	
	printf("읽을 이미지 이름: ");
	fgets(inputName, 30, stdin);
	inputName[strcspn(inputName, "\n")] = 0;
	strcat(fileFullName, inputName);

	if ((image = fopen(fileFullName, "r")) == NULL) {
		printf("이미지를 찾을 수 없습니다.\n");
		return index;
	}  //  입력한 이름의 파일을 찾을 수 없을 경우 에러 출력

	for (i = 0; i < index; i++)
		if (strcmp(inputName, imgList[i]->imgName) == 0) {
			printf("이미 읽은 파일입니다.\n");
			return index;
		}   //  현재까지 로드된 파일들과 비교하여
			//  동일한 이름의 파일이 있을 경우 중복 로드 방지

	imgList[index] = malloc(sizeof(IMGMAT)); // 구조체에 메모리 할당
	fscanf(image, "%d%d%d", &imgList[index]->height,
		&imgList[index]->width, &imgList[index]->compFlag);

	imgList[index]->imgName = malloc((strlen(inputName) + 1) * sizeof(char));  
	imgList[index]->imgValue = malloc(imgList[index]->height * sizeof(int*)); // int** 에 메모리 할당
	for (i = 0; i < imgList[index]->height; i++)
		imgList[index]->imgValue[i] = malloc(imgList[index]->width * sizeof(int)); // int* 에 메모리 할당
	
	strcpy(imgList[index]->imgName, inputName);
	if (imgList[index]->compFlag == 0)
		for (i = 0; i < imgList[index]->height; i++)
			for (j = 0; j < imgList[index]->width; j++)
				fscanf(image, "%d", *(imgList[index]->imgValue + i) + j);  //  압축되지 않은 파일의 경우
																		   //  차례대로 읽어 대입
	else {
		release_compression(imgList, image, index);
	}
	
	fclose(image);
	printf("[%s]를 성공적으로 로드하였습니다.\n", inputName);
	
	return ++index;  //  로드된 이미지 개수 증가
}  //  _2_load_image

/*	============================== release_compression ==============================
	이미지를 로드할 때, 압축되어 있는 파일을 해석하여
	색상 인덱스 값을 구조체에 로드하는 함수
	Pre		텍스트 파일 열린 상태
	Post	이미지 색상 인덱스 저장
*/

void release_compression(IMGMAT* imgList[], FILE* image, int index)
{
	int colorIndex, indexNumber;
	int linearIndex = 0, row, col; //  linearIndex : 1씩 증가하며 구조체의 row와 col을 결정하는 변수
								   //  row와 col은 색상 인덱스를 대입할 이차원 배열의 원소를 결정
	int i;

	while (linearIndex < imgList[index]->height * imgList[index]->width) {
		fscanf(image, "%d", &colorIndex);
		fscanf(image, "%d", &indexNumber);
		for (i = 0; i < indexNumber; i++) {
			row = linearIndex / imgList[index]->width;
			col = linearIndex - row * imgList[index]->width; // 정수의 나눗셈을 활용하여 row, col 구함
			imgList[index]->imgValue[row][col] = colorIndex;
			linearIndex++;
		}
	}
	return;
}  //  release_compression

/*	============================== check_input ==============================
	사용자가 프로그램 사용 중 이미지 번호를 입력했을 때,
	로드된 이미지 개수에 근거하여 입력한 번호에 해당하는 이미지가 존재하는지
	판단하는 함수
	Pre		사용자로부터 이미지 번호 입력을 받음
	Post	문자를 숫자 값으로 변환 (혹은 에러 출력)
*/

int check_input(char *indexchar, int *index, int indexNum)
{
	if (indexchar[1] == '\n') 
		*index = indexchar[0] - '0';  //  입력값이 한 자리라면 그 값을 숫자로 변환
	else if ('0' <= indexchar[1] && indexchar[1] <= '9' && indexchar[2] == '\n')
		*index = (indexchar[0] - '0') * 10 + indexchar[1] - '0'; //  입력값이 두 자리라면 그 값을 숫자로 변환
	else {
		ERROR 1;  //  그 외에는 모두 에러 처리
	}

	if (*index <= 0 || *index > indexNum) {
		ERROR 1;  //  인덱스에 해당하느 이미지가 없을 시 에러 처리
	}
	return 0;
}  //  check_input

/*	============================== _3_do_print ==============================
	사용자로부터 출력할 이미지 번호를 입력받고, 출력 함수를 호출한다.
	Pre		이미지 로드 혹은 없음
	Post	이미지 출력 혹은 에러 출력
*/

void _3_do_print(IMGMAT* imgList[], int indexNum)
{
	char printWhat[20];
	char* startIndexchar, * endIndexchar;
	int startIndex = 0, endIndex = 0;
	int i;

	printf("출력할 이미지 번호나 범위: ");
	fgets(printWhat, 20, stdin);
	printWhat[strcspn(printWhat, "\n")] = 0;

	if (strlen(printWhat) == 0 || printWhat[0] == '-') {
		ERROR;
	}  //  strtok 함수를 사용하기 전 '-'로 문자열이 시작하는 경우를 배제한다.
	   //  "-2-3" 등의 입력이 허용됨을 방지하기 위해서이다.

	startIndexchar = strtok(printWhat, "-");
	endIndexchar = strtok(NULL, "");  //  '-'를 경계로 전후를 나눔

	for (i = 0; i < strlen(startIndexchar); i++) {
		if (startIndexchar[i] < '0' || startIndexchar[i] > '9') {
			ERROR;
		}  //  startIndexchar의 길이만큼 for문을 돌리고 숫자가 아닌 값이 발견되는 즉시 에러 처리
		startIndex += (startIndexchar[i] - '0') * pow(10, strlen(startIndexchar) - 1 - i);
	}  //  문자열이 숫자만으로 이루어져있으면 이를 십진수로 바꾸어 저장한다.
	
	if (endIndexchar == NULL) {  //  범위가 아닌 하나의 숫자를 입력하여 endIndexchar가 null pointer일 때
		if (startIndex <= 0 || startIndex > indexNum) {
			ERROR;
		}  //  입력값에 해당하는 이미지가 없을 시에 에러 출력
		print_image(imgList, startIndex - 1);
	}
	else {
		for (i = 0; i < strlen(endIndexchar); i++) {
			if (endIndexchar[i] < '0' && endIndexchar[i] > '9') {
				ERROR;
			} //  endIndexchar의 길이만큼 for문을 돌리고 숫자가 아닌 값이 발견되는 즉시 에러 처리
			endIndex += (endIndexchar[i] - '0') * pow(10, strlen(endIndexchar) - 1 - i);
		}  //  문자열이 숫자만으로 이루어져있으면 이를 십진수로 바꾸어 저장한다.
		
		if (startIndex <= 0 || endIndex > indexNum || endIndex < startIndex) {
			ERROR;
		}  //  입력값이 유효하지 않을 경우 에러 처리
		for (i = startIndex; i <= endIndex; i++)
			print_image(imgList, i - 1);
	}
	return;
}  //  _3_do_print

/*	============================== print_image ==============================
	색상 인덱스를 이용하여 실제로 이미지를 출력하는 함수.
	에러 처리 과정에서 이미지 출력 명령을 여러 군데에서 내리게 되어
	함수를 따로 만들게 되었음.
	Pre		출력할 이미지 번호 받음
	Post	이미지 출력
*/

void print_image(IMGMAT* imgList[], int index)
{
	int i, j;
	
	for (i = 0; i < imgList[index]->height; i++) {
		for (j = 0; j < imgList[index]->width; j++) {
			if (imgList[index]->compFlag == 0)
				//  출력할 문자의 색상 설정
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), imgList[index]->imgValue[i][j] / 10);
			else
				//  압축된 파일은 색상인덱스가 이미 양자화된 상태이기에 10으로 나누지 않도록 한다
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), imgList[index]->imgValue[i][j]);
			printf("■");
		}
		printf("\n");
	}
	//  글자색 복귀
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n");
}  //  print_image

/*	============================== _4_remove_image ==============================
	로드된 이미지를 삭제하고, 이미지 인덱스를 하나씩 위로 앞당긴다
	Pre		이미지 로드 혹은 없음
	Post	로드된 이미지 제거 혹은 없음
*/

int _4_remove_image(IMGMAT* imgList[], int indexNum)
{
	char indexchar[20];
	int index;
	int i, j;

	printf("삭제할 이미지 번호: ");
	fgets(indexchar, 20, stdin);
	
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  잘못된 입력에 대해 에러 처리

	for (; index < indexNum; index++) {
		imgList[index - 1]->imgName = realloc(imgList[index - 1]->imgName, (strlen(imgList[index]->imgName) + 1) * sizeof(char));
		free(imgList[index - 1]->imgValue);  // 이름 메모리 재할당 및 덮어쓰기
		imgList[index - 1]->imgValue = calloc(imgList[index]->height, sizeof(int*));
		for (int i = 0; i < imgList[index]->height; i++)
			imgList[index - 1]->imgValue[i] = realloc(imgList[index - 1]->imgValue[i], imgList[index]->width * sizeof(int));
		for (i = 0; i < imgList[index]->height; i++)
			for (j = 0; j < imgList[index]->width; j++)
				*(*(imgList[index - 1]->imgValue + i) + j) = *(*(imgList[index]->imgValue + i) + j); //  색상 인덱스 메모리 재할당 및 덮어쓰기
		imgList[index - 1]->height = imgList[index]->height;
		imgList[index - 1]->width = imgList[index]->width;
		imgList[index - 1]->compFlag = imgList[index]->compFlag;
		strcpy(imgList[index - 1]->imgName, imgList[index]->imgName);  //  기타 이미지 정보 덮어쓰기
	}
	if (index == indexNum) {  
		free(imgList[index - 1]->imgName);
		for (i = 0; i < imgList[index - 1]->height; i++)
			free(imgList[index - 1]->imgValue[i]);
		free(imgList[index - 1]->imgValue);
		free(imgList[index - 1]);
	}  //  마지막 번호의 이미지에 도달하면 메모리를 해제한다
	printf("성공적으로 삭제하였습니다.\n");
	return 0;
}

/*	============================== _5_do_compress ==============================
	사용자로부터 압축할 이미지 번호를 입력받아
	압축된 이미지 텍스트 파일을 저장한다
	Pre		이미지 로드 또는 없음
	Post	압축된 이미지 텍스트 파일 저장 또는 없음
*/

void _5_do_compress(IMGMAT* imgList[], int indexNum)
{
	char indexchar[20], newFileName[32], fileFullName[40] = IMG_DIR;
	int index, cmp1, cmp2, colorIndexNum = 1;
	int i, j;
	FILE *img_c;

	printf("압축할 이미지 번호: ");
	fgets(indexchar, 20, stdin);
	
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  유효하지 않은 입력에 대해 에러 처리
	
	if (imgList[index - 1]->compFlag == 1) {
		printf("이미 압축한 파일입니다.\n");
		return 1;
	}  //  이미 압축된 파일 중복 압축 방지

	strcpy(newFileName, imgList[index - 1]->imgName);
	newFileName[strlen(newFileName) - 4] = '\0';  //  '.txt'를 지우기 위해 '.' 위치에 null 문자 대입
	strcat(newFileName, "_c.txt");  //  이미지 이름 뒤에 '_c.txt' 이어붙이기

	strcat(fileFullName, newFileName);
	if ((img_c = fopen(fileFullName, "w")) == NULL)
		printf("[%s]을 생성할 수 없습니다.\n", newFileName);
	
	fprintf(img_c, "%d %d 1\n", imgList[index - 1]->height, imgList[index - 1]->width);
	compress_image(imgList, img_c, index);

	fclose(img_c);
	printf("성공적으로 압축하였습니다. 압축파일명: [%s]\n", newFileName);
	
	return 0;
}  // _5_do_compress_image

/*	============================== compress_image ==============================
	실제로 압축을 진행한다.
	후에 이미지 축소 함수에서도 압축을 사용할 일이 있어
	함수를 따로 정의하였다.
	Pre		압축할 이미지 번호 입력받음, 압축시킬 이미지 텍스트 파일 열림
	Post	압축된 이미지 텍스트 파일 저장
*/

void compress_image(IMGMAT* imgList[], FILE* img_c, int index)
{
	int cmp1, cmp2, colorIndexNum = 1;
	int i, j;

	cmp1 = imgList[index - 1]->imgValue[0][0] / 10;
	for (i = 0; i < imgList[index - 1]->height; i++)
		for (j = 0; j < imgList[index - 1]->width; j++) {
			if (i == 0 && j == 0)
				continue; //  처음에 cmp1에 값을 한 번 대입하였으므로 반복문을 한 번 생략한다
			cmp2 = imgList[index - 1]->imgValue[i][j] / 10;
			if (cmp1 == cmp2)
				colorIndexNum++;  //  순차적으로 이미지 정보를 읽으며 같은 색상인덱스가 반복되는 수를 센다
			else {
				fprintf(img_c, "%d %d ", cmp1, colorIndexNum);
				colorIndexNum = 1;
				cmp1 = cmp2;
			}  //  색상인덱스값이 달라지는 시점에서 이전까지 반복되어 출현했던 색상인덱스와 반복된 횟수를 출력한다.
		}
	fprintf(img_c, "%d %d", cmp2, colorIndexNum);  //  조건문 때문에 마지막으로 반복된 색상 인덱스는 출력되지 않으므로 써줌
	return;
}

/*	============================== _6_reduce_image ==============================
	축소할 이미지 번호를 입력받고, 축소된 이미지 텍스트 파일을 저장한다.
	Pre		이미지 로드됨 또는 없음
	Post	축소된 이미지 텍스트 파일 저장 또는 없음
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

	printf("축소할 이미지 번호: ");
	fgets(indexchar, 20, stdin);
	if (check_input(indexchar, &index, indexNum))
		return 1;  //  유효하지 않은 입력에 대한 에러 처리
	
	if (imgList[index -1]->height / 2 <20 || imgList[index-1]->width / 2 <20) {
		printf("더 이상 축소할 수 없습니다.\n");
		return 1;
	}  //  가로 또는 세로가 20 픽셀 이하일 때 축소를 실행하지 않는다

	strcpy(newFileName, imgList[index - 1]->imgName);
	newFileName[strlen(newFileName) - 4] = '\0'; // 이미지 이름에서 ".txt"를 지우기 위해 '.' 위치에 null 문자 대입
	strcat(newFileName, "_r.txt");
	strcat(fileFullName, newFileName);

	if ((img_r = fopen(fileFullName, "w")) == NULL)
		printf("[%s]을 생성할 수 없습니다.\n", newFileName);
	
	reducedImg[0] = malloc(sizeof(IMGMAT));
	reducedImg[0]->imgValue = calloc(imgList[index - 1]->height / 2, sizeof(int*));
	for (i = 0; i < imgList[index - 1]->height / 2; i++)
		reducedImg[0]->imgValue[i] = calloc(imgList[index - 1]->width / 2, sizeof(int)); // 임시로 선언한 구조체에 메모리 할당

	reducedImg[0]->height = imgList[index - 1]->height / 2;
	reducedImg[0]->width = imgList[index - 1]->width / 2;
	for (i = 0; i < imgList[index - 1]->height - 1; i += 2)
		for (j = 0; j < imgList[index - 1]->width - 1; j += 2) {
			val[0] = imgList[index - 1]->imgValue[i][j];
			val[1] = imgList[index - 1]->imgValue[i][j + 1];
			val[2] = imgList[index - 1]->imgValue[i + 1][j];
			val[3] = imgList[index - 1]->imgValue[i + 1][j + 1];
			// 4개의 픽셀을 하나로 줄이기 위해 하나의 배열에 대입

			mode = find_mode(imgList[index-1]->compFlag, val, freq);  // 색상인덱스의 최고 빈도 값을 얻고
									      // 각 색상 인덱스의 출현 빈도를 배열에 저장
			for (k = 0; k < 4; k++)
				if (freq[k] == mode) {
					reducedImg[0]->imgValue[i / 2][j / 2] = val[k];
					break;
				}  //  우선순위 순서로 검사하여 최빈 색상인덱스가 발견되면 값을 저장
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
				reducedImg[0]->imgValue[i][j] *= 10; // 압축하는 과정에서 색상인덱스를 양자화하는 과정이 있는데,
													 // 이미 압축된 파일을 로드한 경우 색상인덱스가 이미 양자화 되어있으므로 10을 곱해준다

		compress_image(reducedImg, img_r, 1);
	}  //  압축된 파일을 축소하는 경우 파일을 저장할 때 압축하여 저장

	for (i = 0; i < imgList[index - 1]->height / 2; i++)
		free(reducedImg[0]->imgValue[i]);
	free(reducedImg[0]->imgValue);  //  임시로 선언한 구조체 메모리 해제

	fclose(img_r);

	printf("성공적으로 축소하였습니다. 축소파일명: [%s]\n", newFileName);
	return 0;

}  //  _6_reduce_image

/*	============================== find_mode ==============================
	4개의 배열 원소들의 최대 빈도수를 찾고,
	각 원소들의 빈도수를 배열에 저장
	Pre		배열에 양자화된 색상인덱스값 저장
	Post	축소된 이미지 텍스트 파일 저장 또는 없음
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