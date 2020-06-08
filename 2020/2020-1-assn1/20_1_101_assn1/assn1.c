/* Started at 4/25/2020 13:42 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FFLUSH while(getchar()!='\n');

void print_info() {
	int back;
	system("cls");
	while (1) {
		printf("-------------------------- 미니 야구 게임 설명 --------------------------\n");
		printf("\n본 게임은 야구의 룰을 일부 적용한 '미니 야구 게임'입니다.\n");
		printf("\n  1. 게임은 총 3회로 이루어져 있습니다.\n");
		printf("\n  2. 플레이어는 스윙 혹은 공을 거릴 수 있습니다.\n");
		printf("\n  3. 안타를 치거나 볼넷이 되면 출루 할 수 있습니다.\n");
		printf("\n  4. 주자에 의한 아웃은 없으며, 플라이 아웃, 스트라이크 아웃만 있습니다.\n");
		printf("\n  5. 3회까지 득점한 점수가 10점 이상이면 게임에서 승리하게 됩니다. \n");
		printf("--------------------------------------------------------------------------\n");
		printf("메인 메뉴로 돌아가기(-1):");
		scanf("%d", &back); FFLUSH;
		if (back == -1) break;
	}
}

void draw_line() {
	for (int i = 0; i < 50; i++) printf("=");
	printf("\n");
}

int print_menu() {
	char menu;
	system("cls");
	while (1){
		draw_line();
		printf("\n\t\t1. 게임 시작\n");
		printf("\n\t\t2. 게임 설명\n");
		printf("\n\t\t3. 게임 종료\n\n");
		draw_line();

		scanf("%c", &menu); FFLUSH
		if ('1' <= menu && menu <= '3')
			return menu - '0';

		system("cls");
		printf("메뉴를 다시 선택해주세요.\n");
	}
}

void print_score(int cur_in, int cur_score, int fir, int sec, int thr) {
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┐\n");
	printf("│           1회   2회   3회     총 점          │\n");
	switch (cur_in) {
	case 1:
		printf(" 점수       %d \n", cur_score); break;
	case 2:
		printf(" 점수       %d    %d \n", fir, cur_score); break;
	case 3:
		printf(" 점수       %d    %d    %d \n", fir, sec, cur_score); break;
	case 4:
		printf(" 점수       %d    %d    %d       %d \n", fir, sec, thr, fir+sec+thr); break;
	}
	printf("│                                              │\n");
	printf("└━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void print_count(int ball, int strike, int out) {
	int i;
	printf("B ");
	for (i = 0; i < ball; i++) printf("●");
	for (i = 0; i < 3 - ball; i++) printf("○");
	printf("\nS ");
	for (i = 0; i < strike; i++) printf("●");
	for (i = 0; i < 2 - strike; i++) printf("○");
	printf("\nO ");
	for (i = 0; i < out; i++) printf("●");	
	for (i = 0; i < 2 - out; i++) printf("○");
	printf("\n");
}

void print_base(int one, int two, int three) {
	printf("\t        %s\n", two ? "◆" : "◇");
	printf("\t      ↙   ↖ \n");
	printf("\t    ↙       ↖ \n");
	printf("\t  ↙           ↖ \n");
	printf("\t%s               %s \n", three ? "◆" : "◇", one ? "◆" : "◇");
	printf("\t  ↖           ↗ \n");
	printf("\t    ↖       ↗ \n");
	printf("\t      ↖   ↗ \n");
	printf("\t        ◇, \n");
}

int get_swing_result(int is_final, int is_strike_full) {
	int result;
	int prob = rand() % 100	+ 1;
	if (0 < prob && prob <= 14)			result = 1;	// 안타
	else if (14 < prob && prob <= 21)	result = 2;	// 2루타
	else if (21 < prob && prob <= 26)	result = 3;	// 3루타
	else if (26 < prob && prob <= 29)	result = 4;	// 홈런
	else if (29 < prob && prob <= 62)	result = 5;	// 플라이 아웃 29~62
	else if (62 < prob && prob <= 100)	result = 6;	// 스트라이크 62~100

	if (!(is_final && (result == 5 || is_strike_full && result == 6)))
		system("cls");

	switch (result) {
	case 1:	printf("안타입니다.\n");			break;
	case 2: printf("2루타입니다.\n");			break;
	case 3: printf("3루타입니다.\n");			break;
	case 4: printf("홈런입니다!!!!짝짝짝\n");	break;
	case 5: printf("플라이 아웃입니다.\n");		break;
	case 6:
		if (is_strike_full)	printf("스트라이크 아웃!!\n");
		else printf("스트라이크입니다.\n");
	}
	return result;
}

int get_pass_result(int is_final, int is_strike_full, int is_ball_full) {
	int result;
	int prob = rand() % 100 + 1;
	if (0 < prob && prob <= 65)			result = 1;	// 볼
	else if (65 < prob && prob <= 100)	result = 0;	// 스트라이크

	if (!(is_final && is_strike_full && result == 0))
		system("cls");

	if (result) {
		if (is_ball_full) printf("볼넷입니다.\n");
		else printf("볼입니다.\n");
	} else {
		if (is_strike_full) printf("스트라이크 아웃!!\n");
		else printf("스트라이크 입니다.\n");
	}
	return result;
}

int start_inning(int num, int *fir, int *sec, int *thr, int *total) {
	char p_choice;
	int swing_result;
	int base1 = 0, base2 = 0, base3 = 0;
	int ball = 0, strike = 0, out = 0;
	int score = 0;
	int is_new_striker = 0;
	int is_final, is_finished = 0, back;

	while (1) {
		draw_line();
		printf("%d회\n", num);
		print_score(num, score, *fir, *sec, *thr);
		print_count(ball, strike, out);
		print_base(base1, base2, base3);
		is_final = (num >= 3 || *total + score >= 10) && out >= 2;
		printf("1. 스윙\t2. 거르기\n");
		printf("입력: ");
		scanf("%c", &p_choice);	FFLUSH;


		if (p_choice == '1') {
			swing_result = get_swing_result(is_final, strike >= 2);

			is_new_striker = 1;
			switch (swing_result) {
			case 1: // 안타
				if (base3)	printf("\n홈인! 점수를 한 점 올립니다.\n");
				score += base3;
				base3 = base2;
				base2 = base1;
				base1 = 1; break;
			case 2:	// 2루타
				if (base3)	printf("\n3루 주자 홈인! 점수를 한 점 올립니다.\n");
				if (base2)	printf("\n2루 주자 홈인! 점수를 한 점 올립니다.\n");
				score += base2 + base3;
				base3 = base1;
				base2 = 1;
				base1 = 0; break;
			case 3:	// 3루타
				if (base3)	printf("\n3루 주자 홈인! 점수를 한 점 올립니다.\n");
				if (base2)	printf("\n2루 주자 홈인! 점수를 한 점 올립니다.\n");
				if (base1)	printf("\n1루 주자 홈인! 점수를 한 점 올립니다.\n");
				score += base1 + base2 + base3;
				base3 = 1;
				base2 = base1 = 0; break;
			case 4:	// 홈런
				if (base3)	printf("\n3루 주자 홈인! 점수를 한 점 올립니다.\n");
				if (base2)	printf("\n2루 주자 홈인! 점수를 한 점 올립니다.\n");
				if (base1)	printf("\n1루 주자 홈인! 점수를 한 점 올립니다.\n");
				printf("\n타자 홈인! 점수를 한 점 올립니다.\n");
				score += 1 + base1 + base2 + base3;
				base3 = base2 = base1 = 0; break;
			case 5:
				out += 1; break;
			case 6:
				if (strike >= 2) out += 1;
				else {
					strike += 1;
					is_new_striker = 0;
				} break;
			}
			if (is_new_striker)
				ball = strike = 0;

		}
		else if (p_choice == '2') {
			if (get_pass_result(is_final, strike >= 2, ball >= 3)) {
				if (ball >= 3) {
					strike = ball = 0;
					if (!base1)	base1 = 1;
					else {
						if (!base2)	base2 = 1;
						else {
							base3 = 1;
							if (base3) {
								printf("홈인! 점수를 한 점 올립니다.\n");
								score++;
							}
						}
					}
				}
				else	ball += 1;
			}
			else {
				if (strike >= 2) {
					out += 1;
					strike = ball = 0;
				}
				else	strike += 1;
			}
		}
		else {
			system("cls");
			printf("숫자를 다시 입력하세요.\n");
		}

		if (out >= 3) {
			*total += score;
			switch (num) {
			case 1: *fir = score; break;
			case 2: *sec = score; break;
			case 3: *thr = score;
				printf("경기가 종료되었습니다.\n");
				is_finished = 1;
			}
			if (num < 3) {
				printf("이닝이 종료되었습니다.\n");
				if (*total >= 10)	is_finished = 1;
			}
			if (is_finished) {
				print_score(4, 0, *fir, *sec, *thr);
				printf("* 결과: 플레이어%s하였습니다.\n", (*total >= 10) ? "가 승리" : "에게 패배");
				printf("메인 메뉴로 돌아가기(-1) ");
				scanf("%d", &back); FFLUSH;
				return 1;
			}
			return 0;
		}
	}
}
int start_game() {
	int fir = 0, sec = 0, thr = 0, total = 0;
	system("cls");
	draw_line();
	printf("게임을 시작합니다.\n");
	draw_line();
	for (int i = 1; i <= 3; i++)
		if (start_inning(i, &fir, &sec, &thr, &total))
			break;
}

int main()
{
	while (1) {
		srand(time(NULL));
		switch (print_menu()) {
		case 1: start_game(); break;
		case 2: print_info(); break;
		case 3: return 0;
		}
	}
}
