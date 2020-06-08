#ifndef ASSN5_H
#define ASSN5_H

typedef struct node     // 카드 한 장을 나타내는 구조체 변수
{	
	int cardShape;      // 1은 ♠, 2는 ♣, 3은 ◆, 4는 ♥에 대응됨
	char cardNum[3];    // A, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,J ,Q ,K에 해당
	struct node *next;  // 다음 노드를 가리키는 Linked List 구현
} NODE; 
typedef struct  // 덱이 쌓인 상태 및 덱(또는 셋)의 리스트에 대한 정보
{
	int count; // 덱(또는 셋)에 저장된 노드(카드)의 개수
	NODE *head; // 카드가 쌓여있을 때 가장 위에 놓인 카드
	NODE *tail; // 카드가 쌓여있을 때 가장 아래에 놓인 카드
} DECK;

// (functions.c) 덱 변수 초기화 및 초기 소지금 결정
void initializeGame(DECK *d, DECK *pl, DECK *dl,
	int argc, char *argv[], int *iniMoney, int *possession);

// (functions.c) 카드를 생성(또는 재생성)한다.
int setDeck(DECK *d, int code);

// (functions.c) 덱을 새로 생성한다.
int generateCard(DECK *deck, int shape, char num);

// (process.c) 게임 종료 시 1을 반환, 그렇지 않을 경우 0을 반환 
int betting(DECK *d, int iniMoney, int *bet, int *possession); //

// (process.c) 덱을 새로 생성하고, 덱을 셔플한다.
int shuffle(DECK *d);

// (process.c) player, dealer에게 카드를 두 장씩 분배하고, 카드를 출력한다.
int distribute(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (functions.c) dealer(또는 player)에게 카드 한 장을 분배한다.
void giveOneCard(DECK *d, DECK *receiver);

// (functions.c) dealer(또는 player)가 가진 카드 셋을 출력, 카드 넘버의 합을 출력 및 저장한다.
void printCardSet(DECK *object, char* s, int *sum, int code);

// (functions.c) 한 장의 카드를 출력한다.
void printOneCard(int shapeNum, char num[]);

// (functions.c) 카드 넘버를 Game Rule에 따라 숫자로 환산한다. A는 11로 환산한다.
int cvtCardNum(char s[]);

// (functions.c) A의 환산값을 게임 참가자에게 유리한 쪽으로 조정한다.
int A_variation(int sum, int A_indicator);

// (process.c) 카드 분배가 끝난 후, player가 Hit 또는 Stay한다.
int playerTurn(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (process.c) 카드 넘버 합에 따라 dealer의 Hit 또는 Stay를 결정한다.
int dealerTurn(DECK *d, DECK *player, DECK *dealer,
	int *possession, int betMoney, int *numSum);

// (process.c) 게임 룰에 따라 승패를 판정한다.
int judge(int plNumSum, int dlNumSum, DECK *pl, DECK *dl, int bet);

// (functions.c) 덱(또는 셋)을 모두 할당 해제한다.
void freeSet(DECK *set);

#define FFLUSH while(getchar() != '\n');

#endif  //  ASSN5_H
