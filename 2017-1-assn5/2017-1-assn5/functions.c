#include <stdio.h>
#include <stdlib.h>
#include"assn5.h"

// �� ������ �ʱ�ȭ�ϰ�, �ʱ� �������� �����Ѵ�.
void initializeGame(DECK *d, DECK *pl, DECK *dl,
	int argc, char *argv[], int *iniMoney, int *possession)
{
	// �� �ʱ�ȭ
	d->count = 0;
	d->head = NULL;
	d->tail = NULL;

	pl->count = 0;
	pl->head = NULL;
	pl->tail = NULL;

	dl->count = 0;
	dl->head = NULL;
	dl->tail = NULL;

	// �ʱ� ������ ����
	if (argc == 1)
		*iniMoney = 5000;
	if (argc == 2)
		*iniMoney = atoi(argv[1]);
	*possession = *iniMoney;
}  //  initializeGame

// ī�带 ����(�Ǵ� �����)�Ѵ�.
int setDeck(DECK *d, int code)
{
	int i, j;

	if (code == 1)  // ���� ī�尡 �������� ��
		freeSet(d);

	for (i = 1; i <= 4; i++) {
		generateCard(d, i, 'A');
		for (j = 2; j <= 9; j++)
			generateCard(d, i, j + '0');
		generateCard(d, i, '0');  //  ī��ѹ��� 10�� ��� �켱 '0'���� �Ѱ��ش�.
		generateCard(d, i, 'J');
		generateCard(d, i, 'Q');
		generateCard(d, i, 'K');	
	}   // 52���� ī�� ����
}  //  setDeck

// ī�� ���� ���� �����Ѵ�.
int generateCard(DECK *d, int shape, char num)
{
	int i;
	NODE *tmp;

	tmp = (NODE *)malloc(sizeof(NODE));
	
	tmp->cardNum[0] = ' '; // ī��ѹ��� ���ڸ��� ���
	tmp->cardNum[1] = num;
	if (num == '0')
		tmp->cardNum[0] = '1'; // ī��ѹ��� 10(���ڸ�)�� ���
	tmp->cardNum[2] = '\0';
	
	tmp->cardShape = shape;
	tmp->next = NULL;  //  NODE ���� �Ϸ�

	if (d->count == 0)  //  ���� ����� ī�� ������ 0�� ��
	{
		d->head = tmp;
		d->tail = tmp;
	}
	else // ���� 1�� �̻��� ī�尡 ����Ǿ����� �� 
	{
		d->tail->next = tmp;
		d->tail = tmp;
	}
	d->count++;
	
	return 0;
}  //  generateCard

// dealer(�Ǵ� player)���� ī�� �� ���� �й��Ѵ�.
void giveOneCard(DECK *d, DECK *receiver)
{
	NODE *tmp;

	tmp = d->head;  // �� ���� ���� ī�带 �� �� ���´�
	if (receiver->count == 0) // dealer(�Ǵ� player)�� ī�� ���� �� ���
	{
		receiver->head = tmp;
		receiver->tail = tmp;
	}
	else // dealer(�Ǵ� player)�� ������ ī�尡 �����ϴ� ���
	{
		receiver->tail->next = tmp;
		receiver->tail = tmp;
	
	}

	d->head = d->head->next;  // ī�带 �� �� �̾ư����Ƿ� DECK ���� ������Ʈ 
	tmp->next = NULL;  // �̾ư� ī��� DECK ���� ���� ����
	receiver->count++;
	d->count--;
}  //  giveOneCard

//  dealer(�Ǵ� player)�� ���� ī�� ���� ���, ī�� �ѹ��� ���� ��� �� �����Ѵ�.
void printCardSet(DECK *object, char* s, int *numSum, int code)
{
	/*	printCardSet �Լ��� int *sum �Ű�������
		main���� player&dealer�� ī�� �ѹ� sum�� ������Ʈ ���ֱ� ����
		numSum�� �ּҰ��� �����ش�.
		��� numSum�� ������Ʈ���� �ʿ䰡 ���� �ÿ��� &tmp�� �����Ѵ�.
	*/

	int cnt, sum = 0, A_cnt = 0;
	int cardNum;
	NODE *tmp;

	// tmp�� object->head�� ���� �� �ϳ��� next�ذ��� ������� ��ȹ�̴�.
	tmp = object->head;  
	printf("<%s> ", s);  // ī�� ���� ����(?)�� ���

	//  dealer�� ���� ������ dealer�� ù��° ī�带 �����ϸ� �� �ǹǷ� code = 1�� ó�� 
	if (code == 1){
		printf("[????] ");
		tmp = tmp->next;
	}

	// code = 1�� ��� hidden card�� �̹� �ϳ� ��������Ƿ� cnt = 0�� pass
	for (cnt = code; cnt < object->count; cnt++) {
		printOneCard(tmp->cardShape, tmp->cardNum); 
		cardNum = cvtCardNum(tmp->cardNum); // A,2,3,...,K ���� Game Rule�� ���� ���ڷ� ��ȯ
		A_cnt += (cardNum == 11) ? 1 : 0;  // A ���� count
		sum += cardNum;  // ī�� �ѹ� sum ���
		tmp = tmp->next;
	}
	sum = A_variation(sum, A_cnt); // A�� player(�Ǵ� dealer)���� �����ϰ� ���
	printf(" , Sum = %d\n", sum);
	*numSum = sum; // ī�� �ѹ� sum ����
	return;
} // printCardSet

// �� ���� ī�带 ����Ѵ�.
void printOneCard(int shapeNum, char num[])
{
	//  (int)shapeNum�� ���� ī�� ����� ����Ѵ�
	switch (shapeNum) {
	case 1: printf("[��%s] ", num);
		break;
	case 2: printf("[��%s] ", num);
		break; 
	case 3: printf("[��%s] ", num);
		break;
	case 4: printf("[��%s] ", num);
		break;
	}
}  // printOneCard

// ī�� �ѹ��� Game Rule�� ���� ���ڷ� ȯ���Ѵ�. A�� 11�� ȯ���Ѵ�.
int cvtCardNum(char s[])
{
	if (s[1] == 'A')
		return 11;
	else if ('2' <= s[1] && s[1] <= '9')
		return s[1] - '0';
	else 
		return 10;
}  //  cvtCardNum

//  A�� player(�Ǵ� dealer)���� ������ ������ ����Ѵ�.
int A_variation(int sum, int A_num)
{
	// sum�� 21�� ���� �ʰų�, 11�� ����� A ������ 0�� �� ������ Recursion ȣ��
	if (sum > 21 && A_num > 0) 
		return A_variation(sum - 10, --A_num);
	else
		return sum;
}  //  A_variation

//  ��(�Ǵ� ��)�� �ִ� ��� NODE�� �Ҵ� �����Ѵ�.
void freeSet(DECK *set)
{
	NODE *tmp;

	while (set->count > 0) {
		tmp = set->head;
		if (set->count == 1) // ��(�Ǵ� ��)�� ī�尡 �� �� ������ ���
			set->head = NULL;
		else
			set->head = set->head->next;
		free(tmp);
		set->count--;
	}
}  //  freeSet