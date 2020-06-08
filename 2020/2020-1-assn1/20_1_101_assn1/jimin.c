#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_menu(); // 초기 메뉴 
void print_info(); // 게임 설명
void draw_line(); // 줄 긋기 
void start_game(); // 게임 시작 
int start_inning(int inning, int strike, int ball, int out, int base1, int base2,
	int base3, int score, int first_score, int second_score, int third_score, int total_score); // 이닝 시작 
void print_score(int inning, int score, int first_score, int second_score, int third_score, int total_score); // 점수 보여주기
void print_count(int strike, int ball, int out);// 카운트 세기
void print_base(int base1, int base2, int base3);// 주자상황 보여주기
int get_swing_result();// 스윙 결과
int get_pass_result(); // 볼 or 스트라이크

int main()
{

	print_menu();
	start_game();
}

void draw_line()
{
	int a;
	for (a = 1; a <= 50; a++)
	{
		printf("=");
	}
}

void print_info()
{
	printf("---------------------------------------------미니 야구 게임 설명-------------------------\n");
	printf("\n");
	printf(" 본 게임은 야구의 룰을 일부 적용한 '미니 야구 게임'입니다 \n");
	printf("\n");
	printf("1. 게임은 총 3회로 이루어져 있습니다.\n");
	printf("\n");
	printf("2.플레이어는 스윙 혹은 공을 거를 수 있습니다.\n");
	printf("\n");
	printf("3. 안타를 치거나 볼넷이 되면 출루 할 수 있습니다.\n");
	printf("\n");
	printf("4.주자에 의한 아웃은 없으며, 플라이 아웃, 스트라이크 아웃만 있습니다.\n");
	printf("\n");
	printf("5. 3회까지 득점한 점수가 10점 이상이면 게임에서 승리하게 됩니다.\n");
	printf("----------------------------------------------------------------------------------------\n");
	printf("메인 메뉴로 돌아가기(-1):");
}

void print_menu()
{
	int num = 0;
	int minus_one = 0;

	while (num != 1)
	{
		draw_line();
		printf("\n");
		printf("             1. 게임 시작\n");
		printf("             2. 게임 설명\n");
		printf("             3. 게임 종료\n");
		printf("\n");
		draw_line();
		printf("\n");
		printf("선택하고자 하는 메뉴를 입력하세요:");

		scanf("%d", &num);
		switch (num)
		{
		case 1:
			break;

		case 2:
			while (minus_one != -1)
			{

				system("cls");
				print_info();
				scanf("%d", &minus_one);
			}
			minus_one = 0;
			system("cls");
			break;
		case 3:
			printf("프로그램을 종료합니다.");
			return 0;
			break;

		default:
			system("cls");
			printf("메뉴를 다시 선택해주세요.\n");
		}
	}
}  // print_menu 끝

int get_swing_result()
{
	srand(time(NULL));
	int swing_random = rand() % 100;

	if (0 <= swing_random && swing_random < 14)
		return 1;
	else if (14 <= swing_random && swing_random < 21)
		return 2;
	else if (21 <= swing_random && swing_random < 26)
		return 3;
	else if (26 <= swing_random && swing_random < 29)
		return 4;
	else if (29 <= swing_random && swing_random < 62)
		return 5;
	else
		return 6;

}//1- 1루타 , 2- 2루타 , 3-3루타 , 4-홈런 , 5-플라이 아웃 6- 스트라이크 

int get_pass_result()
{
	srand(time(NULL));
	int ball_random = rand() % 100;

	if (0 <= ball_random && ball_random < 65)
		return 7;

	else
		return 6;

} // 6 스트라이크, 7 볼

void print_score(int inning, int score, int first_score, int second_score, int third_score, int total_score)
{
	printf(" ┌--------------------------------------------------------┐\n");
	printf(" │               1회     2회    3회        총점           │\n");
	switch (inning)
	{
	case 1:
		printf("  점수            %d                                        \n ", first_score);
		break;
	case 2:
		printf("  점수            %d     %d                                    \n ", first_score, second_score);
		break;
	case 3:
		printf("  점수            %d     %d     %d                               \n ", first_score, second_score, third_score);
		break;
	default:
		total_score = first_score + second_score + third_score;
		printf("  점수            %d     %d     %d          %d            \n", first_score, second_score, third_score, total_score);
	}
	printf("│                                                        │\n");
	printf(" └--------------------------------------------------------┘\n");

}


int start_inning(int inning, int strike, int ball, int out, int base1,
	int base2, int base3, int score, int first_score, int second_score, int third_score, int total_score)// 스타트이닝
{

	int swing_or_not;


	while (out < 3)
	{

		draw_line();
		printf("\n \n");
		draw_line();
		printf("\n");
		printf("%d 회", inning);
		printf("\n");
		print_score(inning, score, first_score, second_score, third_score, total_score); // 점수 보여주기
		print_count(strike, ball, out);// 카운트 세기
		print_base(base1, base2, base3);// 주자상황 보여주기
		printf("\n 1. 스윙  2.  거르기 \n입력: ");
		scanf(" %d ", &swing_or_not);

		switch (swing_or_not)
		{
		case 1: // 스윙한 경우 

			if (get_swing_result() == 1) //1루타
			{
				printf("안타입니다.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3루 주자 있을 때
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n홈인! 점수를 한 점 올립니다. ");
				}
				if (base2 == 1)//2루 주자 있을 때 
				{
					base3 = 1;
					base2 = 0;
				}
				if (base1 == 1)//1루 주자 있을 때
				{
					base2 = 1;
					base1 = 0;
				}
				base1 = 1;
			}
			else if (get_swing_result() == 2)  // 2루타
			{
				printf("2루타 입니다.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3루 주자 있을 때
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base2 == 1)//2루 주자 있을 때 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base1 == 1)//1루 주자 있을 때
				{
					base3 = 1;
					base1 = 0;
				}
				base2 = 1;
			}

			else if (get_swing_result() == 3)  // 3루타
			{
				printf("3루타 입니다.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3루 주자 있을 때
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base2 == 1)//2루 주자 있을 때 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base1 == 1)//1루 주자 있을 때
				{
					score = score + 1;
					base1 = 0;
					printf("\n\n1루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				base3 = 1;
			}


			else if (get_swing_result() == 4) // 홈런
			{
				printf("홈런입니다.\n");
				strike = 0; ball = 0;
				if (base3 == 1) //3루 주자 있을 때
				{
					score = score + 1;
					base3 = 0;
					printf("\n\n3루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base2 == 1)//2루 주자 있을 때 
				{
					score = score + 1;
					base2 = 0;
					printf("\n\n2루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				if (base1 == 1)//1루 주자 있을 때
				{
					score = score + 1;
					base1 = 0;
					printf("\n\n1루 주자 홈인! 점수를 한 점 올립니다. ");
				}
				score = score + 1;
				printf("\n\n타자 홈인! 점수를 한 점 올립니다.");
			}
			else if (get_swing_result() == 5) // 플라이 아웃
			{
				strike = 0; ball = 0;
				out = out + 1;
				printf("플라이 아웃입니다. \n");
			}
			else // 스윙 시 스트라이크
			{
				strike = strike + 1;
				if (strike == 3)
				{
					out = out + 1;
					strike = 0;
					ball = 0;
					printf("스트라이크 아웃!!\n");
				}
				else
				{
					printf("스트라이크 입니다.\n");
				}
			}
			break;

		case 2: // 거르기 선택시
			if (get_pass_result == 6) // 거르기 시 스트라이크
			{
				strike = strike + 1;
				if (strike == 3)
				{
					out = out + 1;
					strike = 0;
					ball = 0;
					printf("스트라이크 아웃!!\n");
				}
				else
				{
					printf("스트라이크 입니다. \n");

				}
			}
			else
			{
				ball = ball + 1;
				if (ball == 4)
				{
					strike = 0; ball = 0;
					printf("볼넷입니다 \n.");
					if (base1 == 0) // 1루에 없을 때 
					{
						base1 = 1;
					}
					else if (base1 == 1) // 1루에 있을 때
					{
						if (base2 == 1)
						{
							if (base3 == 1) // 주자 만루
							{
								score = score + 1;
							}
							else // 주자 1,2 루 
							{
								base3 = 1;
							}

						}
						else // 1루에 있고 2루에 없을 때
						{
							base2 = 1;

						}

					}

				}
				else
				{
					printf("볼입니다. \n");
				}

			}
			break;
		default: // 1과 2가 아닌 다른 걸 눌렀을 때
			printf("숫자를 다시 입력하십시오.\n");
		}

	}

	strike = 0; ball = 0; out = 0; base1 = 0; base2 = 0; base3 = 0;


	printf("이닝이 종료되었습니다.\n");

	return score;
}

void start_game()
{

	int inning = 1;
	int strike = 0;
	int ball = 0;
	int out = 0;
	int base1 = 0;
	int base2 = 0;
	int base3 = 0;
	int score = 0;
	int first_score = 0;
	int second_score = 0;
	int third_score = 0;
	int total_score = 0;

	draw_line();
	printf("\n게임을 시작합니다.\n");

	while (inning <= 3)
	{
		start_inning(inning, strike, ball, out, base1, base2,
			base3, score, first_score, second_score, third_score, total_score);


		if (inning == 1)
			first_score = score;
		else if (inning == 2)
			second_score = score;
		else if (inning == 3)
			third_score = score;

		inning = inning + 1;

		score = 0;

	}


}

void print_base(int base1, int base2, int base3)
{
	printf("\n");
	switch (base1)
	{
	case 0:
		if (base2 == 0)
		{
			if (base3 == 0) // 주자 없음 
			{
				printf("              ◇              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◇                          ◇\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
			else  //주자 3루 
			{
				printf("              ◇              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◆                          ◇\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
		}
		else
		{
			if (base3 == 0) // 주자 2루
			{
				printf("              ◆              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◇                          ◇\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");

			}
			else // 주자 2,3루
			{
				printf("              ◆              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◆                          ◇\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
		}

		break;
	case 1:
		if (base2 == 0)
		{
			if (base3 == 0) // 주자 1루
			{
				printf("              ◇              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◇                          ◆\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
			else  //주자 1, 3루 
			{
				printf("              ◇              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◆                          ◆\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
		}
		else
		{
			if (base3 == 0) // 주자 1, 2루
			{
				printf("              ◆              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◇                          ◆\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");

			}
			else // 주자 만루
			{
				printf("              ◆              \n");
				printf("           ↙    ↖           \n");
				printf("       ↙            ↖       \n");
				printf("   ↙                    ↖   \n");
				printf("◆                          ◆\n");
				printf("   ↘                    ↗   \n");
				printf("       ↘            ↗       \n");
				printf("           ↘    ↗           \n");
				printf("              ◇              \n");
			}
		}
	}
}

void print_count(int strike, int ball, int out)
{
	printf("\n");
	switch (ball)
	{
	case 0:
		printf("B ○○○\n");
		break;
	case 1:
		printf("B ●○○\n");
		break;
	case 2:
		printf("B ●●○\n");
		break;
	case 3:
		printf("B ●●●\n");
		break;

	}
	switch (strike)
	{
	case 0:
		printf("S ○○\n");
		break;
	case 1:
		printf("S ●○\n");
		break;
	case 2:
		printf("S ●●\n");
		break;

	}
	switch (out)
	{
	case 0:
		printf("O ○○\n");
		break;
	case 1:
		printf("O ●○\n");
		break;
	case 2:
		printf("O ●●\n");
		break;

	}

}