#include <stdio.h>

#pragma warning (disable:4996)

int encode(char c, int prevPoint);

int main() {
	int round = 0, oneScore;
	char scoreInput, finalScore;
	int curScore = 0;
	int plusScore = 0, cnt1 = 0, cnt2 = 0;
	char fname[20];
	FILE* f;

	printf("File to read: ");
	scanf("%s", fname);
	f = fopen(fname, "r");
	if (f == NULL) {
		printf("cannot open %s\n", fname);
		return 0;
	}

	while (1) {
		curScore += plusScore;
		plusScore = 0;
		round++;

		if (round == 10) {
			fscanf(f, "%c%c", &scoreInput, &finalScore);
			printf("%c%c", scoreInput, finalScore);

			oneScore = encode(scoreInput, 0);
			if (cnt1 > 0) { plusScore += oneScore; cnt1--; }
			if (cnt2 > 0) { plusScore += oneScore; cnt2--; }
			curScore += oneScore;

			oneScore = encode(finalScore, scoreInput);
			if (cnt1 > 0) { plusScore += oneScore; cnt1--; }
			if (cnt2 > 0) { plusScore += oneScore; cnt2--; }
			curScore += oneScore;

			curScore += plusScore;
			if (scoreInput != 'S' && finalScore != 'P')
				break;

			fscanf(f, "%c", &scoreInput);
			printf("%c", scoreInput);
			curScore += encode(scoreInput, oneScore);
			break;
		}

		fscanf(f, "%c", &scoreInput);
		printf("%c", scoreInput);

		oneScore = encode(scoreInput, 0);
		if (cnt1 > 0) { plusScore += oneScore; cnt1--; }
		if (cnt2 > 0) { plusScore += oneScore; cnt2--; }
		curScore += oneScore;

		if (scoreInput == 'S') {
			if (cnt1 > 0) if (cnt2 == 0) cnt2 = 2; else printf("WHAT???\n");
			else cnt1 = 2;
			continue;
		}
		
		fscanf(f, "%c", &scoreInput);
		printf("%c", scoreInput);

		oneScore = encode(scoreInput, oneScore);
		if (cnt1 > 0) { plusScore += oneScore; cnt1--; }
		if (cnt2 > 0) { plusScore += oneScore; cnt2--; }
		curScore += oneScore;
		if (scoreInput == 'P') {
			if (cnt1 > 0) if (cnt2 == 0) cnt2 = 1; else printf("WHAT??\n");
			else cnt1 = 1;
		}
		
	}
	fclose(f);
	printf("\nTOTAL SCORE: %d\n", curScore);
}

int encode(char c, int prevPoint) {
	switch (c) {
	case 'S': return 10;
	case '-': return 0;
	case 'P': return 10 - prevPoint;
	default:
		if ('0' <= c && c <= '9') return c - '0';
		else {
			printf("FATAL ERROR\n");
			exit(1);
		}
	}
}