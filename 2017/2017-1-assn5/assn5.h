#ifndef ASSN5_H
#define ASSN5_H

typedef struct node     // ī�� �� ���� ��Ÿ���� ����ü ����
{	
	int cardShape;      // 1�� ��, 2�� ��, 3�� ��, 4�� ���� ������
	char cardNum[3];    // A, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,J ,Q ,K�� �ش�
	struct node *next;  // ���� ��带 ����Ű�� Linked List ����
} NODE; 
typedef struct  // ���� ���� ���� �� ��(�Ǵ� ��)�� ����Ʈ�� ���� ����
{
	int count; // ��(�Ǵ� ��)�� ����� ���(ī��)�� ����
	NODE *head; // ī�尡 �׿����� �� ���� ���� ���� ī��
	NODE *tail; // ī�尡 �׿����� �� ���� �Ʒ��� ���� ī��
} DECK;

// (functions.c) �� ���� �ʱ�ȭ �� �ʱ� ������ ����
void initializeGame(DECK *d, DECK *pl, DECK *dl,
	int argc, char *argv[], int *iniMoney, int *possession);

// (functions.c) ī�带 ����(�Ǵ� �����)�Ѵ�.
int setDeck(DECK *d, int code);

// (functions.c) ���� ���� �����Ѵ�.
int generateCard(DECK *deck, int shape, char num);

// (process.c) ���� ���� �� 1�� ��ȯ, �׷��� ���� ��� 0�� ��ȯ 
int betting(DECK *d, int iniMoney, int *bet, int *possession); //

// (process.c) ���� ���� �����ϰ�, ���� �����Ѵ�.
int shuffle(DECK *d);

// (process.c) player, dealer���� ī�带 �� �徿 �й��ϰ�, ī�带 ����Ѵ�.
int distribute(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (functions.c) dealer(�Ǵ� player)���� ī�� �� ���� �й��Ѵ�.
void giveOneCard(DECK *d, DECK *receiver);

// (functions.c) dealer(�Ǵ� player)�� ���� ī�� ���� ���, ī�� �ѹ��� ���� ��� �� �����Ѵ�.
void printCardSet(DECK *object, char* s, int *sum, int code);

// (functions.c) �� ���� ī�带 ����Ѵ�.
void printOneCard(int shapeNum, char num[]);

// (functions.c) ī�� �ѹ��� Game Rule�� ���� ���ڷ� ȯ���Ѵ�. A�� 11�� ȯ���Ѵ�.
int cvtCardNum(char s[]);

// (functions.c) A�� ȯ�갪�� ���� �����ڿ��� ������ ������ �����Ѵ�.
int A_variation(int sum, int A_indicator);

// (process.c) ī�� �й谡 ���� ��, player�� Hit �Ǵ� Stay�Ѵ�.
int playerTurn(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (process.c) ī�� �ѹ� �տ� ���� dealer�� Hit �Ǵ� Stay�� �����Ѵ�.
int dealerTurn(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (process.c) ���� �꿡 ���� ���и� �����Ѵ�.
int judge(int plNumSum, int dlNumSum, DECK *pl, DECK *dl, int bet);

// (functions.c) ��(�Ǵ� ��)�� ��� �Ҵ� �����Ѵ�.
void freeSet(DECK *set);

#define FFLUSH while(getchar() != '\n');

#endif  //  ASSN5_H
