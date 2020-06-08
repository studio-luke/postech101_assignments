#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable:4996)
#define FFLUSH while(getchar()!='\n');
#define MAX 4
#define MAX_MIXING_COUNT 100
void print_board(int board[][MAX], char rboard[][MAX], int round);//������ ���
int check_input(int pc[], int board[][MAX], char rboard[][MAX]);//��ĭ ���� �ֳ�?
void init_board(int board[][MAX], char rboard[][MAX]);//������ �ʱ�ȭ
int start_game(int* player, int playersc[], int board[][MAX], char rboard[][MAX], int pc[], int round);//���� ���� �Լ�
void swap(int* a, int* b);//��ġ ��ȯ

enum error {hello, world};

int hi() {
	return hello;
}

int main() {
	srand(time(NULL));
	int board[MAX][MAX] = { 0 }, round = 0, player, pc[4] = { 0 }, playersc[2] = { 0 };//������ ��¥ ��, round�� ù ȭ�鿡�� board�� �����ֱ� ���� ���, player�� 1 �Ǵ� 2, pc�� playerchoice, playersc==playerscore
	char rboard[MAX][MAX] = { '\0' };//�÷��̾�� ���̴� ����
	player = rand() % 2 + 1;//�÷��̾� 1 �Ǵ� 2
	while (1) {
		printf("Memorize the board number!!\n\n");
		init_board(board, rboard);//���� �� �ʱ�ȭ
		print_board(board, rboard, round);//���� ���
		Sleep(3000);
		round += 1;//round�� 0�̸� board�� ��µǹǷ�
		system("cls");
		print_board(board, rboard, round);//rboard ���
		if (start_game(&player, playersc, board, rboard, pc, round) == 12) {//���� ���� ����
			printf("Good bye");
			break;
		}
		else {//���� ��� ����
			printf("New Game!\n");
			round = 0;//�ٽ� board�� ������־���ϹǷ�
		}
	}
	return 0;//����
}
void print_board(int board[][MAX], char rboard[][MAX], int round) {//�������
	int i, s;
	printf("\n    ");
	for (i = 0; i < MAX; i++)
		printf("  %d ", i);//�� �̸� ���
	printf("\n");
	for (i = 0; i < MAX; i++) {
		printf("    +---+---+---+---+\n");//���м�
		printf("  %d |", i);//�� ���
		for (s = 0; s < MAX; s++)
			printf(" %c |", (round == 0) ? board[i][s] + '0' : rboard[i][s]);//ó�� �����ִ� �Ÿ� board, �� ���Ŀ� rboard ���
		printf("\n");
	}
	printf("    +---+---+---+---+\n");//���м�
}
void init_board(int board[][MAX], char rboard[][MAX]) {//���� �ʱ�ȭ
	int i, s, arr[MAX * MAX] = { 0 }, k = 0;//16���� index�� ������ �迭(1122334455667788�� ���� ��)
	for (i = 0; i < 8; i++) {//arr�� 2���� ���� ���� �Է�(1122334455667788�� ��������)
		arr[2 * i] = i + 1;
		arr[2 * i + 1] = i + 1;
	}
	for (i = 0; i < MAX_MIXING_COUNT; i++)//arr�� ������
		swap(&arr[rand() % (MAX * MAX)], &arr[rand() % (MAX * MAX)]);
	for (i = 0; i < MAX; i++)
		for (s = 0; s < MAX; s++) {
			board[i][s] = arr[k];//�����ϰ� ���� arr�� board�� �������
			k++;//k�� ������Ŵ���ν� for �ι��� Ƚ���� ��� ��� ����
			rboard[i][s] = '*';//��� �� *�� �ǵ���
		}
}
int check_input(int pc[], int board[][MAX], char rboard[][MAX]) {//input�� ���� ĭ�� ����Ű�ų� �̹� ���� ĭ�� ����Ű�°��� ���� ���� �Ǵ�
	int i, re = 0;
	if ((pc[0] == pc[2])/*�� ����*/ && (pc[1] == pc[3])/*�� ����*/)
		return 10;
	for (i = 0; i < 2; i++) {//�̹� ���� ĭ?
		if (rboard[pc[2 * i]][pc[2 * i + 1]] != '*')
			return 20;
	}
	return (board[pc[0]][pc[1]] == board[pc[2]][pc[3]]) ? (1) : (0);//���� ĭ�� ���ڰ� ������ 1�� return, �ƴϸ� 0����
}
int start_game(int* player, int playersc[], int board[][MAX], char rboard[][MAX], int pc[], int round) {//���� ����
	int i, c;
	char yorn;
	printf("\n\n[player %d] : ", *player);//���� �÷��̾� ���
	for (i = 0; i < MAX; i++)
		scanf("%d", &pc[i]);//�÷��̾ �Է��� �� ���� ���� ����
	c = check_input(pc, board, rboard);//������ ��ȿ�� �Ǵ�
	if (c == 10 || c == 20) {//���ų� �̹� ���� ī�� ���� ��
		(c == 10) ? printf("\nsame card... try again...\n") ://������ ī�� �Է� ��
			printf("\nalready open... try again...\n");//�̹� ���� ī�带 �������� ��
		start_game(player, playersc, board, rboard, pc, round);//�ٽ� ȣ���Ͽ� �Է� �ٽ� ����
	}
	else if (c != 1) {//���� ī���� ���� �ٸ�
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = board[pc[2 * i]][pc[2 * i + 1]] + '0';//rboard�� board�� �־� ī�� ���� ȿ��
		print_board(board, rboard, round);//���
		printf("\nMismatch!!\n");
		Sleep(3000);
		system("cls");//�����
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = '*';//���� ī�带 �ٽ� ������ �ϱ� ���� *�� ��� ���� �־���
		*player = ((*player == 1) ? (2) : (1));//1���� �÷��� ������ �÷��̾ 2�� ��.
		print_board(board, rboard, round);//���� ���
		start_game(player, playersc, board, rboard, pc, round);
		return 10;
	}
	else {//���� ī�� ���� ����
		for (i = 0; i < 2; i++)
			rboard[pc[2 * i]][pc[2 * i + 1]] = board[pc[2 * i]][pc[2 * i + 1]] + '0';//ī�� ���� ȿ��
		playersc[(*player == 1) ? 0 : 1] += 1;//�÷��̾��� ���� �ø�
		print_board(board, rboard, round);//���� ī�� ���
		printf("\nplayer %d get score!!\n", *player);
		printf("----------------------------\n");
		printf("[player 1] %d : %d [player 2]\n", playersc[0], playersc[1]);//�������
		printf("----------------------------\n\n");
		if (playersc[0] + playersc[1] == 8) {//��� ī�� ������ ��
			if (playersc[0] == playersc[1])//����
				printf("Game End! Draw!\n");
			else//������ �̱�
				printf("Game End! Player %d wins!\n", (playersc[0] > playersc[1]) ? 1 : 2);
			for (i = 0; i < 2; i++)
				playersc[i] = 0;
			printf("Continue? (y/n) "); FFLUSH;//�ٽ�?
			scanf("%c", &yorn); FFLUSH;
			return (yorn == 'y') ? (11) : (12);//�ٽ� �ϸ� 11, �ƴϸ� 12����
		}
		printf("player %d get one more chance!!\n", *player);//��� ���� ������ �ƴҶ��� �����.(return ����)
		start_game(player, playersc, board, rboard, pc, round);//�ش� �Լ� �ٽ� ȣ���ؼ� ���� �÷��̾��� �Է� ����
	}
}
void swap(int* a, int* b) {//��ġ ��ȭ
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}