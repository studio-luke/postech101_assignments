#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"assn5.h"

// 소지금 및 사용자 명령에 따라 게임 종료 여부를 결정하고, 배팅 금액을 입력받는다.
int betting(DECK *d, int iniMoney, int *bet, int *possession)
{
	if (*possession == 0) {
		printf("재산이 없어서 카지노에서 쫓겨났습니다...\n");
		printf("역시 올인은 안돼요...\n\n");
		freeSet(d);  //  덱 할당 해제
		return 1; //  게임 종료 시 1을 반환
	}
	if (*possession >= 100 * iniMoney) {
		printf("당신은 돈을 너무 많이 벌어 카지노 업체가 당신을 쫓아냈습니다.\n");
		printf("카지노에서 $%d으로 무려 $%d을 벌었습니다!!!\n\n", iniMoney, *possession);
		freeSet(d);
		return 1;
	}
	while (1) {
		printf("[현재 소지금 : $%d] 배팅 금액 설정하세요! <0 for Exit> ", *possession);
		scanf("%d", bet); FFLUSH;
		
		if (*bet > 0 && *bet <= *possession) {
			*possession -= *bet; // 소지금에서 배팅 금액 차감
			break;
		}
		else if (*bet == 0) {
			printf("당신은 $%d을 들고 와서 $%d을 남겨왔습니다.\n\n", iniMoney, *possession);
			freeSet(d);
			return 1; 
		}
		else {
			printf("\n유효한 배팅 금액을 설정해주세요!\n");
			continue;
		}
	}

	return 0; // 게임 계속 진행 시 0을 반환
} //  betting

// 덱을 새로 생성하고, 덱을 셔플한다.
int shuffle(DECK *d)
{
	/*	셔플은 가장 보편적인 셔플 방법을 구현한다.
		덱 중간의 임의의 지점으로부터 임의의 개수만큼의 카드를 꺼내
		덱 위에 얹는다.
	*/
	int start_shuf, size;  
	int cnt, i;
	int code = 0; // code : 처음 덱을 생성하는 경우 0, 게임 중간에 덱을 재생성하는 경우 1
	NODE *tmp, *tmp_s, *tmp_e;

	if (d->count == 0) // 덱의 카드 개수가 0인 경우, 즉 처음 덱을 생성하는 경우
		setDeck(d, code);
	else if (d->count <= 26) // 덱의 카드 개수가 26개 이하로 카드 재생성이 필요한 경우
	{
		code = 1;
		printf("\n카드를 새롭게 섞습니다...  ");
		setDeck(d, code);
	}
	else
		return 1; // 그 외의 경우 함수 종료, 셔플 안할 시에 1 반환

	for (cnt = 0; cnt < 10000; cnt++) {
		start_shuf = rand() % 51 + 1;  //  start_shuf: 셔플 시작 지점,
		size = rand() % (52 - start_shuf) + 1; // size : 이동할 카드 개수

		tmp_s = d->head;
		for (i = 0; i < start_shuf; i++)
			tmp_s = tmp_s->next;  // tmp_s : 셔플하는 카드 중 맨 위의 카드를 가리킴

		tmp_e = tmp_s; 
		for (i = 0; i < size - 1; i++)
			tmp_e = tmp_e->next; // tmp_e : 셔플하는 카드 중 맨 아래의 카드를 가리킴

		tmp = d->head;
		for (i = 0; i < start_shuf - 1; i++)
			tmp = tmp->next; // tmp : tmp_s 바로 이전의 카드를 가리킴

		tmp->next = tmp_e->next; // tmp 다음에 tmp_e의 바로 다음 카드를 연결
		tmp_e->next = d->head;  // tmp_e 다음에 기존 덱의 맨 위의 카드를 연결
		d->head = tmp_s; // 덱의 맨 위 카드가 달라졌으므로 DECK 변수 정보 업데이트
	}

	if (code) // 덱을 재생성 및 셔플하는 경우 Break를 걸어줌
	{
		printf("(Press Enter)");
		while (getchar() != '\n');
	}
	return 0; // 셔플 완료
}  // shuffle

// player, dealer에게 카드를 두 장씩 분배하고, 카드를 출력한다.
int distribute(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int tmp = 0;

	system("cls");  //  화면 초기화
	printf("[소지금 : %d], [배팅금액 : %d]\n", *possession, betMoney);
	printf("-----------------------------------\n");

	giveOneCard(d, player);
	giveOneCard(d, dealer);
	giveOneCard(d, player);
	giveOneCard(d, dealer);

	printCardSet(dealer, "Dealer", &tmp, 1); // &tmp / 0, 1 기능 : functions.c의 함수 정의 주석 참조
	printCardSet(player, "Player", numSum, 0);
	
	if (*numSum == 21) // 카드가 두 장이고 합이 21이면 BLACKJACK이다
	{
		printf("\n★B★L★A★C★K★J★A★C★K★\n");
		printf("배팅한 금액의 3배에 해당하는 $%d을 획득했습니다!\n", betMoney * 3);
		*possession += betMoney * 3;
		freeSet(player);
		freeSet(dealer);  //  player&dealer의 카드 셋 할당 해제
		return 1; // 이번 게임을 종료
	}
	return 0; // 정상 진행
}  //  distribute

// 카드 분배가 끝난 후, player가 Hit 또는 Stay한다.
int playerTurn(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int cnt, tmp;
	char order[20];

	while (1) {
		printf("\nHit or Stay? ");
		scanf("%s", order); FFLUSH;

		for (cnt = 0; cnt < 4; cnt++) // 4 : 유효한 문자열 input의 최대 길이("stay")
			if ('A' <= order[cnt] && order[cnt] <= 'Z')
				order[cnt] += 32;  // 대문자이면, 소문자로 변환("Hit", "sTAy" 입력 허용)

		if (strcmp(order, "hit") == 0) {
			system("cls");
			printf("[소지금 : %d], [배팅금액 : %d]\n", *possession, betMoney);
			printf("-----------------------------------\n");
			giveOneCard(d, player); // player에게 카드 한 장 지급
			printCardSet(dealer, "Dealer", &tmp, 1);
			printCardSet(player, "Player", numSum, 0);
			if (*numSum > 21)
				break; // 카드 넘버 sum이 21을 초과할 경우 player 차례 자동 종료
			else
				continue;
		}
		else if (strcmp(order, "stay") == 0)
			break;
		else
			printf("\n유효한 명령어를 입력해주세요.\n");
	}
} // playerTurn

// 카드 넘버 합에 따라 dealer의 Hit 또는 Stay를 결정한다.
int dealerTurn(DECK *d, DECK *player, DECK *dealer, int *possession, int betMoney, int *numSum)
{
	int tmp = 0;

	system("cls");
	printf("[소지금 : %d], [배팅금액 : %d]\n", *possession, betMoney);
	printf("-----------------------------------\n");
	printCardSet(dealer, "Dealer", numSum, 0);
	printCardSet(player, "Player", &tmp, 0);

	while (1) {
		if (*numSum <= 16) {
			printf("\n딜러가 Hit합니다....  ");
			giveOneCard(d, dealer);
			printf(" (Press Enter)");
			while (getchar() != '\n');

			system("cls");
			printf("[소지금 : %d], [배팅금액 : %d]\n", *possession, betMoney);
			printf("-----------------------------------\n");
			printCardSet(dealer, "Dealer", numSum, 0);
			printCardSet(player, "Player", &tmp, 0);
		}
		else {
			printf("\n딜러가 Stay합니다.\n");
			return 0;
		}
	}
}  //  dealerTurn

int judge(int plNumSum, int dlNumSum, DECK *pl, DECK *dl, int bet)
{
	int earnMoney = 0;
	
	printf("-----------------------------------\n");
	if (plNumSum > 21) {
		printf("버스트!	플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n\n");
	}
	else if (dlNumSum == 21 && dl->count == 2) {
		printf("딜러가 ★B★L★A★C★K★J★A★C★K★\n");
		printf("배팅한 돈을 잃었습니다.\n\n");
	}
	else if (dlNumSum > 21 || plNumSum >= dlNumSum) {
		earnMoney = bet * 2;
		printf("플레이어가 이겼습니다! $%d을 획득했습니다.\n\n", earnMoney);
	}
	else if (plNumSum < dlNumSum)
		printf("플레이어가 졌습니다. 배팅한 돈을 잃었습니다.\n\n");
	else {
		printf("예외 발생!! 게임을 무효처리 합니다.\n\n");
		earnMoney = bet;
	}
	freeSet(pl);
	freeSet(dl); // dealer&player의 카드 셋 할당 해제

	return earnMoney;
} // judge