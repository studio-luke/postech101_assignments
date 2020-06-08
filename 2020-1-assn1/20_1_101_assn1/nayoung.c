#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	FILE* infile, * outfile;
	int sid, mid, fin;
	float avg = 0;
	int count = 0;

	infile = fopen("score.txt", "r");
	fscanf(infile, "%d %d %d", &sid, &mid, &fin);

	if (infile == NULL)
	{
		printf("could not open input file\n");
		return 100;
	}

	outfile = fopen("report.txt", "w");

	fprintf(outfile, "===============================================\n");
	fprintf(outfile, " ÇÐ¹ø     ÃÑÁ¡(ÇÐÁ¡)\n");
	fprintf(outfile, "===============================================\n");

	while (fscanf(infile, "%d %d %d", &sid, &mid, &fin) != EOF)
	{
		float total = (float)mid * 0.4 + fin * 0.6;
		avg += total;
		count++;

		if (90 <= total) fprintf(outfile, "%d     %.1f  (A)\n", sid, total);
		else if (80 <= total && total < 90) fprintf(outfile, "%d     %.1f  (B)\n", sid, total);
		else if (70 <= total && total < 80) fprintf(outfile, "%d     %.1f  (C)\n", sid, total);
		else if (60 <= total && total < 70) fprintf(outfile, "%d     %.1f  (D)\n", sid, total);
		else fprintf(outfile, "%d     %.1f  (E)\n", sid, total);
		return;
	}
	fprintf(outfile, "===============================================\n");
	fprintf(outfile, " Æò±Õ     %.1f\n", (float)avg / count);
	fprintf(outfile, "===============================================\n");

	fclose(infile);
	fclose(outfile);

	return 0;
}