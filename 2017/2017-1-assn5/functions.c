#include <stdio.h>
#include <stdlib.h>
#include"assn5.h"

// 덱 변수를 초기화하고, 초기 소지금을 결정한다.
void initializeGame(DECK *d, DECK *pl, DECK *dl,
	int argc, char *argv[], int *iniMoney, int *possession)
{
	// 덱 초기화
	d->count = 0;
	d->head = NULL;
	d->tail = NULL;

	pl->count = 0;
	pl->head = NULL;
	pl->tail = NULL;

	dl->count = 0;
	dl->head = NULL;
	dl->tail = NULL;

	// 초기 소지금 결정
	if (argc == 1)
		*iniMoney = 5000;
	if (argc == 2)
		*iniMoney = atoi(argv[1]);
	*possession = *iniMoney;
}  //  initializeGame

// 카드를 생성(또는 재생성)한다.
int setDeck(DECK *d, int code)
{
	int i, j;

	if (code == 1)  // 덱에 카드가 남아있을 때
		freeSet(d);

	for (i = 1; i <= 4; i++) {
		generateCard(d, i, 'A');
		for (j = 2; j <= 9; j++)
			generateCard(d, i, j + '0');
		generateCard(d, i, '0');  //  카드넘버가 10인 경우 우선 '0'만을 넘겨준다.
		generateCard(d, i, 'J');
		generateCard(d, i, 'Q');
		generateCard(d, i, 'K');	
	}   // 52장의 카드 생성
}  //  setDeck

// 카드 덱을 새로 생성한다.
int generateCard(DECK *d, int shape, char num)
{
	int i;
	NODE *tmp;

	tmp = (NODE *)malloc(sizeof(NODE));
	
	tmp->cardNum[0] = ' '; // 카드넘버가 한자리인 경우
	tmp->cardNum[1] = num;
	if (num == '0')
		tmp->cardNum[0] = '1'; // 카드넘버가 10(두자리)인 경우
	tmp->cardNum[2] = '\0';
	
	tmp->cardShape = shape;
	tmp->next = NULL;  //  NODE 생성 완료

	if (d->count == 0)  //  덱에 저장된 카드 개수가 0일 때
	{
		d->head = tmp;
		d->tail = tmp;
	}
	else // 덱에 1개 이상의 카드가 저장되어있을 때 
	{
		d->tail->next = tmp;
		d->tail = tmp;
	}
	d->count++;
	
	return 0;
}  //  generateCard

// dealer(또는 player)에게 카드 한 장을 분배한다.
void giveOneCard(DECK *d, DECK *receiver)
{
	NODE *tmp;

	tmp = d->head;  // 덱 가장 위의 카드를 한 장 집는다
	if (receiver->count == 0) // dealer(또는 player)의 카드 셋이 빈 경우
	{
		receiver->head = tmp;
		receiver->tail = tmp;
	}
	else // dealer(또는 player)가 소지한 카드가 존재하는 경우
	{
		receiver->tail->next = tmp;
		receiver->tail = tmp;
	
	}

	d->head = d->head->next;  // 카드를 한 장 뽑아갔으므로 DECK 정보 업데이트 
	tmp->next = NULL;  // 뽑아간 카드와 DECK 사이 연결 해제
	receiver->count++;
	d->count--;
}  //  giveOneCard

//  dealer(또는 player)가 가진 카드 셋을 출력, 카드 넘버의 합을 출력 및 저장한다.
void printCardSet(DECK *object, char* s, int *numSum, int code)
{
	/*	printCardSet 함수의 int *sum 매개변수는
		main에서 player&dealer의 카드 넘버 sum을 업데이트 해주기 위해
		numSum의 주소값을 보내준다.
		고로 numSum을 업데이트해줄 필요가 없을 시에는 &tmp를 대입한다.
	*/

	int cnt, sum = 0, A_cnt = 0;
	int cardNum;
	NODE *tmp;

	// tmp에 object->head를 받은 후 하나씩 next해가며 출력해줄 계획이다.
	tmp = object->head;  
	printf("<%s> ", s);  // 카드 셋의 주인(?)을 출력

	//  dealer의 차례 전에는 dealer의 첫번째 카드를 공개하면 안 되므로 code = 1로 처리 
	if (code == 1){
		printf("[????] ");
		tmp = tmp->next;
	}

	// code = 1의 경우 hidden card를 이미 하나 출력했으므로 cnt = 0을 pass
	for (cnt = code; cnt < object->count; cnt++) {
		printOneCard(tmp->cardShape, tmp->cardNum); 
		cardNum = cvtCardNum(tmp->cardNum); // A,2,3,...,K 등을 Game Rule에 따라 숫자로 변환
		A_cnt += (cardNum == 11) ? 1 : 0;  // A 개수 count
		sum += cardNum;  // 카드 넘버 sum 계산
		tmp = tmp->next;
	}
	sum = A_variation(sum, A_cnt); // A를 player(또는 dealer)에게 유리하게 계산
	printf(" , Sum = %d\n", sum);
	*numSum = sum; // 카드 넘버 sum 저장
	return;
} // printCardSet

// 한 장의 카드를 출력한다.
void printOneCard(int shapeNum, char num[])
{
	//  (int)shapeNum에 따라 카드 모양을 출력한다
	switch (shapeNum) {
	case 1: printf("[♠%s] ", num);
		break;
	case 2: printf("[♣%s] ", num);
		break; 
	case 3: printf("[◆%s] ", num);
		break;
	case 4: printf("[♥%s] ", num);
		break;
	}
}  // printOneCard

// 카드 넘버를 Game Rule에 따라 숫자로 환산한다. A는 11로 환산한다.
int cvtCardNum(char s[])
{
	if (s[1] == 'A')
		return 11;
	else if ('2' <= s[1] && s[1] <= '9')
		return s[1] - '0';
	else 
		return 10;
}  //  cvtCardNum

//  A를 player(또는 dealer)에게 유리한 쪽으로 계산한다.
int A_variation(int sum, int A_num)
{
	// sum이 21을 넘지 않거나, 11로 계산한 A 개수가 0이 될 때까지 Recursion 호출
	if (sum > 21 && A_num > 0) 
		return A_variation(sum - 10, --A_num);
	else
		return sum;
}  //  A_variation

//  덱(또는 셋)에 있는 모든 NODE를 할당 해제한다.
void freeSet(DECK *set)
{
	NODE *tmp;

	while (set->count > 0) {
		tmp = set->head;
		if (set->count == 1) // 덱(또는 셋)에 카드가 한 장 남았을 경우
			set->head = NULL;
		else
			set->head = set->head->next;
		free(tmp);
		set->count--;
	}
}  //  freeSet