#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"assn5.h"

// ������ �� ����� ��ɿ� ���� ���� ���� ���θ� �����ϰ�, ���� �ݾ��� �Է¹޴´�.
int betting(DECK *d, int iniMoney, int *bet, int *possession)
{
	if (*possession == 0) {
		printf("����� ��� ī���뿡�� �Ѱܳ����ϴ�...\n");
		printf("���� ������ �ȵſ�...\n\n");
		freeSet(d);  //  �� �Ҵ� ����
		return 1; //  ���� ���� �� 1�� ��ȯ
	}
	if (*possession >= 100 * iniMoney) {
		printf("����� ���� �ʹ� ���� ���� ī���� ��ü�� ����� �ѾƳ½��ϴ�.\n");
		printf("ī���뿡�� $%d���� ���� $%d�� �������ϴ�!!!\n\n", iniMoney, *possession);
		freeSet(d);
		return 1;
	}
	while (1) {
		printf("[���� ������ : $%d] ���� �ݾ� �����ϼ���! <0 for Exit> ", *possession);
		scanf("%d", bet); FFLUSH;
		
		if (*bet > 0 && *bet <= *possession) {
			*possession -= *bet; // �����ݿ��� ���� �ݾ� ����
			break;
		}
		else if (*bet == 0) {
			printf("����� $%d�� ��� �ͼ� $%d�� ���ܿԽ��ϴ�.\n\n", iniMoney, *possession);
			freeSet(d);
			return 1; 
		}
		else {
			printf("\n��ȿ�� ���� �ݾ��� �������ּ���!\n");
			continue;
		}
	}

	return 0; // ���� ��� ���� �� 0�� ��ȯ
} //  betting

// ���� ���� �����ϰ�, ���� �����Ѵ�.
int shuffle(DECK *d)
{
	/*	������ ���� �������� ���� ����� �����Ѵ�.
		�� �߰��� ������ �������κ��� ������ ������ŭ�� ī�带 ����
		�� ���� ��´�.
	*/
	int start_shuf, size;  
	int cnt, i;
	int code = 0; // code : ó�� ���� �����ϴ� ��� 0, ���� �߰��� ���� ������ϴ� ��� 1
	NODE *tmp, *tmp_s, *tmp_e;

	if (d->count == 0) // ���� ī�� ������ 0�� ���, �� ó�� ���� �����ϴ� ���
		setDeck(d, code);
	else if (d->count <= 26) // ���� ī�� ������ 26�� ���Ϸ� ī�� ������� �ʿ��� ���
	{
		code = 1;
		printf("\nī�带 ���Ӱ� �����ϴ�...  ");
		setDeck(d, code);
	}
	else
		return 1; // �� ���� ��� �Լ� ����, ���� ���� �ÿ� 1 ��ȯ

	for (cnt = 0; cnt < 10000; cnt++) {
		start_shuf = rand() % 51 + 1;  //  start_shuf: ���� ���� ����,
		size = rand() % (52 - start_shuf) + 1; // size : �̵��� ī�� ����

		tmp_s = d->head;
		for (i = 0; i < start_shuf; i++)
			tmp_s = tmp_s->next;  // tmp_s : �����ϴ� ī�� �� �� ���� ī�带 ����Ŵ

		tmp_e = tmp_s; 
		for (i = 0; i < size - 1; i++)
			tmp_e = tmp_e->next; // tmp_e : �����ϴ� ī�� �� �� �Ʒ��� ī�带 ����Ŵ

		tmp = d->head;
		for (i = 0; i < start_shuf - 1; i++)
			tmp = tmp->next; // tmp : tmp_s �ٷ� ������ ī�带 ����Ŵ

		tmp->next = tmp_e->next; // tmp ������ tmp_e�� �ٷ� ���� ī�带 ����
		tmp_e->next = d->head;  // tmp_e ������ ���� ���� �� ���� ī�带 ����
		d->head = tmp_s; // ���� �� �� ī�尡 �޶������Ƿ� DECK ���� ���� ������Ʈ
	}

	if (code) // ���� ����� �� �����ϴ� ��� Break�� �ɾ���
	{
		printf("(Press Enter)");
		while (getchar() != '\n');
	}
	return 0; // ���� �Ϸ�
}  // shuffle

// player, dealer���� ī�带 �� �徿 �й��ϰ�, ī�带 ����Ѵ�.
int distribute(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int tmp = 0;

	system("cls");  //  ȭ�� �ʱ�ȭ
	printf("[������ : %d], [���ñݾ� : %d]\n", *possession, betMoney);
	printf("-----------------------------------\n");

	giveOneCard(d, player);
	giveOneCard(d, dealer);
	giveOneCard(d, player);
	giveOneCard(d, dealer);

	printCardSet(dealer, "Dealer", &tmp, 1); // &tmp / 0, 1 ��� : functions.c�� �Լ� ���� �ּ� ����
	printCardSet(player, "Player", numSum, 0);
	
	if (*numSum == 21) // ī�尡 �� ���̰� ���� 21�̸� BLACKJACK�̴�
	{
		printf("\n��B��L��A��C��K��J��A��C��K��\n");
		printf("������ �ݾ��� 3�迡 �ش��ϴ� $%d�� ȹ���߽��ϴ�!\n", betMoney * 3);
		*possession += betMoney * 3;
		freeSet(player);
		freeSet(dealer);  //  player&dealer�� ī�� �� �Ҵ� ����
		return 1; // �̹� ������ ����
	}
	return 0; // ���� ����
}  //  distribute

// ī�� �й谡 ���� ��, player�� Hit �Ǵ� Stay�Ѵ�.
int playerTurn(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int cnt, tmp;
	char order[20];

	while (1) {
		printf("\nHit or Stay? ");
		scanf("%s", order); FFLUSH;

		for (cnt = 0; cnt < 4; cnt++) // 4 : ��ȿ�� ���ڿ� input�� �ִ� ����("stay")
			if ('A' <= order[cnt] && order[cnt] <= 'Z')
				order[cnt] += 32;  // �빮���̸�, �ҹ��ڷ� ��ȯ("Hit", "sTAy" �Է� ���)

		if (strcmp(order, "hit") == 0) {
			system("cls");
			printf("[������ : %d], [���ñݾ� : %d]\n", *possession, betMoney);
			printf("-----------------------------------\n");
			giveOneCard(d, player); // player���� ī�� �� �� ����
			printCardSet(dealer, "Dealer", &tmp, 1);
			printCardSet(player, "Player", numSum, 0);
			if (*numSum > 21)
				break; // ī�� �ѹ� sum�� 21�� �ʰ��� ��� player ���� �ڵ� ����
			else
				continue;
		}
		else if (strcmp(order, "stay") == 0)
			break;
		else
			printf("\n��ȿ�� ��ɾ �Է����ּ���.\n");
	}
} // playerTurn

// ī�� �ѹ� �տ� ���� dealer�� Hit �Ǵ� Stay�� �����Ѵ�.
int dealerTurn(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int tmp = 0;

	system("cls");
	printf("[������ : %d], [���ñݾ� : %d]\n", *possession, betMoney);
	printf("-----------------------------------\n");
	printCardSet(dealer, "Dealer", numSum, 0);
	printCardSet(player, "Player", &tmp, 0);

	while (1) {
		if (*numSum <= 16) {
			printf("\n������ Hit�մϴ�....  ");
			giveOneCard(d, dealer);
			printf(" (Press Enter)");
			while (getchar() != '\n');

			system("cls");
			printf("[������ : %d], [���ñݾ� : %d]\n", *possession, betMoney);
			printf("-----------------------------------\n");
			printCardSet(dealer, "Dealer", numSum, 0);
			printCardSet(player, "Player", &tmp, 0);
		}
		else {
			printf("\n������ Stay�մϴ�.\n");
			return 0;
		}
	}
}  //  dealerTurn

int judge(int plNumSum, int dlNumSum, DECK *pl, DECK *dl, int bet)
{
	int earnMoney = 0;
	
	printf("-----------------------------------\n");
	if (plNumSum > 21) {
		printf("����Ʈ!	�÷��̾ �����ϴ�. ������ ���� �Ҿ����ϴ�.\n\n");
	}
	else if (dlNumSum == 21 && dl->count == 2) {
		printf("������ ��B��L��A��C��K��J��A��C��K��\n");
		printf("������ ���� �Ҿ����ϴ�.\n\n");
	}
	else if (dlNumSum > 21 || plNumSum >= dlNumSum) {
		earnMoney = bet * 2;
		printf("�÷��̾ �̰���ϴ�! $%d�� ȹ���߽��ϴ�.\n\n", earnMoney);
	}
	else if (plNumSum < dlNumSum)
		printf("�÷��̾ �����ϴ�. ������ ���� �Ҿ����ϴ�.\n\n");
	else {
		printf("���� �߻�!! ������ ��ȿó�� �մϴ�.\n\n");
		earnMoney = bet;
	}
	freeSet(pl);
	freeSet(dl); // dealer&player�� ī�� �� �Ҵ� ����

	return earnMoney;
} // judge