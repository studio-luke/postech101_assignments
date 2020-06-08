#include<stdlib.h>
#include<time.h>
#include"assn5.h"

int main(int argc, char* argv[])
{	
	int iniMoney, possession, bet;
	int plNumSum = 0, dlNumSum = 0;
	DECK deck, playerSet, dealerSet;

	initializeGame(&deck, &playerSet, &dealerSet,
		argc, argv, &iniMoney, &possession);
	srand(time(NULL));
	
	while (1) {
		if (betting(&deck, iniMoney, &bet, &possession))
			break;
		shuffle(&deck);
		if (distribute(&deck, &playerSet, &dealerSet, &possession, bet, &plNumSum))
			continue;
		playerTurn(&deck, &playerSet, &dealerSet, &possession, bet, &plNumSum);
		dealerTurn(&deck, &playerSet, &dealerSet, &possession, bet, &dlNumSum);
		possession += judge(plNumSum, dlNumSum, &playerSet, &dealerSet, bet);
	}
	printf("Press Enter to quit..."); FFLUSH;
	return 0;
} // main