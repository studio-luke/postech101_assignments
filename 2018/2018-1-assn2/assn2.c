#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FFLUSH while(getchar() != '\n')

void draw_line();
char show_menu();
int game_start();
void print_stairs(int pMove, int cMove, int sNum);
void print_RPS(int d1, int d2);
void generate_two_numbers(int *n1, int *n2);
int computer_choose(int cnum1, int cnum2, int pnum1, int pnum2);
void print_paper_rock();
void print_rock_scissors();
void print_scissors_paper();
void print_paper();
void print_rock();
void print_scissors();
void show_record(int playerWin, int computerWin);


int main() {
	char cmd;
	int playerWin = 0, computerWin = 0;

	srand(time(NULL));
	while (1) {
		switch (show_menu()) {
		case '1':
			if (game_start() == 1)
				playerWin += 1;
			else
				computerWin += 1;
			break;
		case '2':
			show_record(playerWin, computerWin);
			break;
		case '3':	
			system("cls");
			printf("\n");
			draw_line();
			printf("\t\t陛嬪夥嬪爾! ж釭 貍晦 橾!擊 п憮\n\n");
			printf("\t\t檜曹 餌塋檜 啗欽擊 螃落棲棻.\n\n");
			printf("\t\t鼻渠爾棻 試盪 啗欽擊 賅舒 螃腦賊 蝓葬м棲棻!\n\n");
			printf("\t\t陛嬪朝 1, 夥嬪朝 2, 爾朝 3戲煎 殮溘ж貊\n\n");
			printf("\t\t陛嬪煎 檜晦賊 1蘊, 夥嬪煎 檜晦賊 2蘊,\n\n");
			printf("\t\t爾煎 檜晦賊 3蘊擊 螃落棲棻.\n\n");
			draw_line();
			printf("詭景煎 給嬴陛溥賊 縛攪 酈蒂 殮溘ж撮蹂...");
			FFLUSH;
			break;
		case '4':
			printf("啪歜擊 謙猿ж衛啊蝗棲梱? (y/n) ");
			scanf("%c", &cmd); FFLUSH;
			if (cmd == 'y' || cmd == 'Y') {
				printf("啪歜擊 謙猿м棲棻... (Press Enter)"); FFLUSH;
				return 0;
			}
			break;
		default: system("cls");
			continue;
		}
	}

}

void draw_line() {
	int i;
	for (i = 0; i < 40; i++)
		printf("十");
	printf("\n\n");
	
	return;
}

char show_menu() {
	char cmd;
	system("cls");
	printf("\n");
	draw_line();
	printf("\t\t\t1. 啪歜 衛濛\n\n");
	printf("\t\t\t2. 瞪瞳 塽 蝓睦\n\n");
	printf("\t\t\t3. 啪歜 撲貲\n\n");
	printf("\t\t\t4. 啪歜 謙猿\n\n");
	draw_line();
	printf("詭景 廓�� 殮溘 >> ");
	scanf("%c", &cmd); FFLUSH;

	return cmd;
}

int game_start() {
	int numStair;
	int playMove = 0, compMove = 0;
	char decision1, decision2, pick;
	int Cdecision1, Cdecision2, Cpick;
	char cmd;
	char isQuit = 0;

	system("cls");
	while (1) {
		printf("\n啪歜擊 嬪и 啗欽曖 偃熱蒂 殮溘<彰嬪: 10~30> >> ");
		scanf("%d", &numStair); FFLUSH;
		if (numStair < 10 || numStair > 30)
			continue;
		break;
	}

	while (1) {
		print_stairs(playMove, compMove, numStair);
		if (playMove == numStair) {
			printf("\n");
			draw_line();
			printf("  ≠  ≠ Ы溯檜橫 譆謙 蝓葬 ≠  ≠  \n\n");
			draw_line();
			printf("詭景煎 給嬴陛溥賊 縛攪 酈蒂 殮溘ж撮蹂...");
			FFLUSH;
			return 1;
		}
		if (compMove == numStair) {
			printf("\n");
			draw_line();
			printf("  ≠  ≠ 闡У攪 譆謙 蝓葬 ≠  ≠  \n\n");
			draw_line();
			printf("詭景煎 給嬴陛溥賊 縛攪 酈蒂 殮溘ж撮蹂...");
			FFLUSH;
			return -1;
		}

		while (1) {
			printf("舒 偃蒂 摹鷗п輿撮蹂: 陛嬪<1>, 夥嬪<2>, 爾<3> >> ");
			scanf("%c %c", &decision1, &decision2); FFLUSH;
			if (decision1 < '1' || decision1 > '3' ||
				decision2 < '1' || decision2 > '3' || decision1 == decision2) continue;
			break;
		}
		generate_two_numbers(&Cdecision1, &Cdecision2);

		printf("\n[闡У攪曖 �贍窟\n");
		print_RPS(Cdecision1, Cdecision2);
		printf("\n[Ы溯檜橫曖 �贍窟\n");
		print_RPS(decision1 - '0', decision2 - '0');

		while (1) {
			printf("\n萃 醞 ж釭蒂 摹鷗п輿撮蹂: ");
			switch (decision1 + decision2 - 2 * '0') {
			case 3: printf("夥嬪<2>, 陛嬪<1>  "); break;
			case 4: printf("陛嬪<1>, 爾<3>  "); break;
			case 5: printf("爾<3>, 夥嬪<2>  "); break;
			default: printf("\nFATAL ERROR!!\n"); exit(1);
		}
			printf("(晦掏:0) >> ");
			scanf("%c", &pick); FFLUSH;
			if (pick == '0') {
				printf("檜廓 啪歜擊 ん晦ж衛啊蝗棲梱?<y/n> >> ");
				scanf("%c", &cmd); FFLUSH;
				if (cmd == 'y' || cmd == 'Y') { isQuit = 1; break; }
				else continue;
			}
			if (pick != decision1 && pick != decision2) continue;
			break;
		}
		if (isQuit) return -1;

		Cpick = computer_choose(Cdecision1, Cdecision2, decision1 - '0', decision2 - '0');

		printf("\n[闡У攪 譆謙摹鷗!]\n");
		switch (Cpick) {
		case 1: print_scissors(); break;
		case 2: print_rock(); break;
		case 3: print_paper(); break;
		default: printf("FATAL ERROR!"); exit(1);
		}

		printf("\n[Ы溯檜橫 譆謙 摹鷗!]\n");
		switch (pick) {
		case '1': print_scissors(); break;
		case '2': print_rock(); break;
		case '3': print_paper(); break;
		default: printf("FATAL ERROR!"); exit(1);
		}

		switch (win_lose_draw(Cpick, pick - '0')) {
		case -1: printf("闡У攪陛 檜啣蝗棲棻!!\n");
			compMove += Cpick;
			if (compMove > numStair) compMove = numStair; break;
		case 0: printf("綠啣蝗棲棻!!\n"); break;
		case 1: printf("Ы溯檜橫陛 檜啣蝗棲棻!!\n");
			playMove += pick - '0';
			if (playMove > numStair) playMove = numStair; break;
		}


		printf("\n啗樓ж溥賊 縛攪酈蒂 殮溘ж撮蹂...");
		FFLUSH;
	}

}

void generate_two_numbers(int *n1, int *n2) {
	*n1 = rand() % 3 + 1;
	do *n2 = rand() % 3 + 1;
	while (*n1 == *n2);
}

int computer_choose(int cnum1, int cnum2, int pnum1, int pnum2) {
	if (cnum1 + cnum2 == pnum1 + pnum2) {
		switch (cnum1) {
		case 1: if (cnum2 == 2) return 2;
				else return 1; break;
		case 2: if (cnum2 == 1) return 2;
				else return 3; break;
		case 3: if (cnum2 == 1) return 1;
				else return 3; break;
		}
	}
	if (rand() % 2 == 0) 
		return cnum1;
	else 
		return cnum2;
}

void print_stairs(int pMove, int cMove, int sNum) {
	int i;
	int x, y;
	const int mapXsiz = sNum + 1;
	const int mapYsiz = (sNum + 1) / 2 + 1;
	
	const int pXPos = pMove;
	const int pYPos = sNum / 2.0 - abs(sNum / 2.0 - pMove);
	const int cXPos = sNum - cMove;
	const int cYPos = sNum / 2.0 - abs(sNum / 2.0 - cMove);

	/*char** stair = (char**)malloc(mapYsiz * sizeof(char*));
	for (i = 0; i < mapXsiz / 2 + 1; i++)
		*(stair + i) = (char*)malloc((sNum + 1) * sizeof(char));
		

	for (y = 0; y < mapYsiz; y++)
		for (x = 0; x < mapXsiz; x++) {
			if (x <= (y - 1) || x >= mapXsiz - 1 - (y - 1))
				stair[y][x] = 1;
			else stair[y][x] = 0;
		}

	stair[pYPos][pXPos] = 2;
	stair[cYPos][cXPos] = 3;
	if (pYPos == cYPos && pXPos == cXPos)
		stair[pYPos][pXPos] = 4;*/

	system("cls");
	printf("識 啗欽熱: %d\n", sNum);
	printf("PLAYER: ∞ < %d>\n", pMove);
	printf("COMPUTER: ≒ < %d>\n", cMove);
	printf("\n");

	for (y = 0; y < mapYsiz; y++) {
		for (x = 0; x < mapXsiz; x++) {
			if (x <= (y - 1) || x >= mapXsiz - 1 - (y - 1))
				printf("十");
			else if (x == pXPos && y == pYPos) {
				if (x == cXPos && y == cYPos)
					printf("〣");
				else
					printf("∞");
			}
			else if (x == cXPos && y == cYPos)
				printf("≒");
			else
				printf("  ");

			/*switch (stair[y][x]) {
			case 1: printf("十"); break;
			case 0: printf("  "); break;
			case 2: printf("∞"); break;
			case 3: printf("≒"); break;
			case 4: printf("〣"); break;
			default: printf("FATAL ERROR!"); exit(1);
			}*/
		}
		printf("\n");
	}
	printf("\n");

}


void print_RPS(int d1, int d2) {
	switch (d1 + d2) {
	case 3: print_rock_scissors(); break;
	case 4: print_scissors_paper(); break;
	case 5: print_paper_rock(); break;
	default: printf("FATAL ERROR!"); exit(1);
	}
}

int win_lose_draw(int cp, int pp) {
	enum result {WIN = 1, LOSE = -1, DRAW = 0};
	
	switch (pp) {
	case 1: if (cp == 1) return DRAW;
			else if (cp == 2) return LOSE;
			else if (cp == 3) return WIN;
			else printf("ERROR\n"); exit(1);
	case 2: if (cp == 1) return WIN;
			else if (cp == 2) return DRAW;
			else if (cp == 3) return LOSE;
			else printf("ERROR\n"); exit(1);
	case 3: if (cp == 1) return LOSE;
			else if (cp == 2) return WIN;
			else if (cp == 3) return DRAW;
			else printf("ERROR\n"); exit(1);
	default: printf("FATAL ERROR!"); exit(1);
	}
}

void print_paper_rock() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                              弛弛                              弛\n");
	printf("弛      十十十十十              弛弛        十十十                弛\n");
	printf("弛     十十十                   弛弛     十十十十十               弛\n");
	printf("弛   十十十十十十十十十十十     弛弛   十十十十十十十             弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十十十十十十 弛弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十           弛弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十十十十十   弛弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十十             弛\n");
	printf("弛   十十十十十十十十十十十     弛弛   十十十十十十               弛\n");
	printf("弛     十十十十十               弛弛     十十十十                 弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}
void print_rock_scissors() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                              弛弛        十十                  弛\n");
	printf("弛        十十十                弛弛      十十                    弛\n");
	printf("弛     十十十十十               弛弛     十十                     弛\n");
	printf("弛   十十十十十十十             弛弛   十十十十十十十十十十十     弛\n");
	printf("弛 十十十十十十十十十           弛弛 十十十十十十十               弛\n");
	printf("弛 十十十十十十十十十           弛弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十十           弛弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十十           弛弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十               弛\n");
	printf("弛   十十十十十十               弛弛   十十十十十                 弛\n");
	printf("弛     十十十十                 弛弛     十十十                   弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}
void print_scissors_paper() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛        十十                  弛弛                              弛\n");
	printf("弛      十十                    弛弛      十十十十十              弛\n");
	printf("弛     十十                     弛弛     十十十                   弛\n");
	printf("弛   十十十十十十十十十十十     弛弛   十十十十十十十十十十十     弛\n");
	printf("弛 十十十十十十十               弛弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十十十十十十十十 弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十             弛弛 十十十十十十十十十十十十十   弛\n");
	printf("弛 十十十十十十十               弛弛 十十十十十十十十             弛\n");
	printf("弛   十十十十十                 弛弛   十十十十十十十十十十十     弛\n");
	printf("弛     十十十                   弛弛     十十十十十               弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}

void print_paper() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                              弛\n");
	printf("弛      十十十十十              弛\n");
	printf("弛     十十十                   弛\n");
	printf("弛   十十十十十十十十十十十     弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十十十十十十十 弛\n");
	printf("弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十十十十十   弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛   十十十十十十十十十十十     弛\n");
	printf("弛     十十十十十               弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}
void print_rock() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                              弛\n");
	printf("弛        十十十                弛\n");
	printf("弛     十十十十十               弛\n");
	printf("弛   十十十十十十十             弛\n");
	printf("弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十十           弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛   十十十十十十               弛\n");
	printf("弛     十十十十                 弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}
void print_scissors() {
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛        十十                  弛\n");
	printf("弛      十十                    弛\n");
	printf("弛     十十                     弛\n");
	printf("弛   十十十十十十十十十十十     弛\n");
	printf("弛 十十十十十十十               弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十十             弛\n");
	printf("弛 十十十十十十十               弛\n");
	printf("弛   十十十十十                 弛\n");
	printf("弛     十十十                   弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
}

void show_record(int playerWin, int computerWin) {
	system("cls");
	draw_line();
	printf("\t\t\t蝓葬:\t%d\n\n", playerWin);
	printf("\t\t\tぬ寡:\t%d\n\n", computerWin);
	if (playerWin + computerWin == 0)
		printf("\t\t\t蝓睦:\t0.00%%\n\n");
	else
		printf("\t\t\t蝓睦:\t%.2f\%%\n\n", (float)playerWin / (playerWin + computerWin) * 100);
	draw_line();
	printf("詭景煎 給嬴陛溥賊 縛攪 酈蒂 殮溘ж撮蹂...");
	FFLUSH;
}
