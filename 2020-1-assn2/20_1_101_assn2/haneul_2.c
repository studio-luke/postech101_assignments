#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable:4996)
#define FFLUSH while(getchar()!='\n');
#define MAX 4
#define MAX_MIXING_COUNT 100
void print_board(int board[][MAX], char rboard[][MAX], int round);//보드판 출력
int check_input(int pc[], int board[][MAX], char rboard[][MAX]);//두칸 열수 있나?
void init_board(int board[][MAX], char rboard[][MAX]);//보드판 초기화
int start_game(int* player, int playersc[], int board[][MAX], char rboard[][MAX], int pc[], int round);//게임 시작 함수
void swap(int* a, int* b);//위치 변환

enum error {hello, world};

int hi() {
	return hello;
}

int main() {
	srand(time(NULL));
	int board[MAX][MAX] = { 0 }, round = 0, player, pc[4] = { 0 }, playersc[2] = { 0 };//보드의 진짜 값, round는 첫 화면에서 board를 보여주기 위해 사용, player는 1 또는 2, pc는 playerchoice, playersc==playerscore
	char rboard[MAX][MAX] = { '\0' };//플레이어에게 보이는 보드
	player = rand() % 2 + 1;//플레이어 1 또는 2
	while (1) {
		printf("Memorize the board number!!\n\n");
		init_board(board, rboard);//보드 값 초기화
		print_board(board, rboard, round);//보드 출력
		Sleep(3000);
		round += 1;//round가 0이면 board가 출력되므로
		system("cls");
		print_board(board, rboard, round);//rboard 출력
		if (start_game(&player, playersc, board, rboard, pc, round) == 12) {//게임 종료 선택
			printf("Good bye");
			break;
		}
		else {//게임 계속 선택
			printf("New Game!\n");
			round = 0;//다시 board를 출력해주어야하므로
		}
	}
	return 0;//종료
}
void print_board(int board[][MAX], char rboard[][MAX], int round) {//보드출력
	int i, s;
	printf("\n    ");
	for (i = 0; i < MAX; i++)
		printf("  %d ", i);//열 이름 출력
	printf("\n");
	for (i = 0; i < MAX; i++) {
		printf("    +---+---+---+---+\n");//구분선
		printf("  %d |", i);//행 출력
		for (s = 0; s < MAX; s++)
			printf(" %c |", (round == 0) ? board[i][s] + '0' : rboard[i][s]);//처음 보여주는 거면 board, 그 이후엔 rboard 출력
		printf("\n");
	}
	printf("    +---+---+---+---+\n");//구분선
}
void init_board(int board[][MAX], char rboard[][MAX]) {//보드 초기화
	int i, s, arr[MAX * MAX] = { 0 }, k = 0;//16개의 index를 가지는 배열(1122334455667788을 가질 것)
	for (i = 0; i < 8; i++) {//arr에 2개의 같은 수를 입력(1122334455667788을 가지도록)
		arr[2 * i] = i + 1;
		arr[2 * i + 1] = i + 1;
	}
	for (i = 0; i < MAX_MIXING_COUNT; i++)//arr를 섞어줌
		swap(&arr[rand() % (MAX * MAX)], &arr[rand() % (MAX * MAX)]);
	for (i = 0; i < MAX; i++)
		for (s = 0; s < MAX; s++) {
			board[i][s] = arr[k];//랜덤하게 섞인 arr를 board에 집어넣음
			k++;//k를 증가시킴으로써 for 두번의 횟수를 모두 고려 가능
			rboard[i][s] = '*';//출력 시 *가 되도록
		}
}
int check_input(int pc[], int board[][MAX], char rboard[][MAX]) {//input이 같은 칸을 가리키거나 이미 열린 칸을 가리키는가에 대한 여부 판단
	int i, re = 0;
	if ((pc[0] == pc[2])/*행 동일*/ && (pc[1] == pc[3])/*열 동일*/)
		return 10;
	for (i = 0; i < 2; i++) {//이미 열린 칸?
		if (rboard[pc[2 * i]][pc[2 * i + 1]] != '*')
			return 20;
	}
	return (board[pc[0]][pc[1]] == board[pc[2]][pc[3]]) ? (1) : (0);//열린 칸의 숫자가 같으면 1을 return, 아니면 0리턴
}
int start_game(int* player, int playersc[], int board[][MAX], char rboard[][MAX], int pc[], int round) {//게임 진행
	int i, c;
	char yorn;
	printf("\n\n[player %d] : ", *player);//현재 플레이어 출력
	for (i = 0; i < MAX; i++)
		scanf("%d", &pc[i]);//플레이어가 입력한 네 개의 숫자 저장
	c = check_input(pc, board, rboard);//숫자의 유효성 판단
	if (c == 10 || c == 20) {//같거나 이미 열린 카드 선택 시
		(c == 10) ? printf("\nsame card... try again...\n") ://동일한 카드 입력 시
			printf("\nalready open... try again...\n");//이미 열린 카드를 선택했을 때
		start_game(player, playersc, board, rboard, pc, round);//다시 호출하여 입력 다시 받음
	}
	else if (c != 1) {//열린 카드의 숫자 다름
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = board[pc[2 * i]][pc[2 * i + 1]] + '0';//rboard에 board를 넣어 카드 열린 효과
		print_board(board, rboard, round);//출력
		printf("\nMismatch!!\n");
		Sleep(3000);
		system("cls");//지우고
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = '*';//열린 카드를 다시 닫히게 하기 위해 *을 모든 값에 넣어줌
		*player = ((*player == 1) ? (2) : (1));//1번이 플레이 했으면 플레이어가 2가 됨.
		print_board(board, rboard, round);//보드 출력
		start_game(player, playersc, board, rboard, pc, round);
		return 10;
	}
	else {//열린 카드 숫자 같음
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = board[pc[2 * i]][pc[2 * i + 1]] + '0';//카드 열린 효과
		playersc[(*player == 1) ? 0 : 1] += 1;//플레이어의 점수 올림
		print_board(board, rboard, round);//열린 카드 출력
		printf("\nplayer %d get score!!\n", *player);
		printf("----------------------------\n");
		printf("[player 1] %d : %d [player 2]\n", playersc[0], playersc[1]);//점수출력
		printf("----------------------------\n\n");
		if (playersc[0] + playersc[1] == 8) {//모든 카드 열렸을 때
			if (playersc[0] == playersc[1])//동점
				printf("Game End! Draw!\n");
			else//누군가 이김
				printf("Game End! Player %d wins!\n", (playersc[0] > playersc[1]) ? 1 : 2);
			for (i = 0; i < 2; i++)
				playersc[i] = 0;
			printf("Continue? (y/n) "); FFLUSH;//다시?
			scanf("%c", &yorn); FFLUSH;
			return (yorn == 'y') ? (11) : (12);//다시 하면 11, 아니면 12리턴
		}
		printf("player %d get one more chance!!\n", *player);//경기 종료 조건이 아닐때만 실행됨.(return 때문)
		start_game(player, playersc, board, rboard, pc, round);//해당 함수 다시 호출해서 같은 플레이어의 입력 진행
	}
}
void swap(int* a, int* b) {//위치 변화
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}