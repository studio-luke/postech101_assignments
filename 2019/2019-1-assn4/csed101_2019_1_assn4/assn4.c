#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <Windows.h>


#define WIDTH 60
#define MAX_LINES 1000

#define PAGE_HEIGHT 10

#define FFLUSH while(getchar()!='\n');

void init(int* num_line, char* line[]);
void load_text(int* num_line, char* line[], FILE* f);

void reader(char* article[], int* num_line);

int main() {
	int num_line;
	char* line[MAX_LINES];
	
	init(&num_line, line);

	reader(line, &num_line);


}

void init(int* num_line, char* line[]) {
	char fname[30];
	FILE* f;

	while (1) {
		printf("* Text File Viewer *\n\n");
		printf("filename: ");
		scanf("%s", fname); FFLUSH;

		f = fopen(fname, "r");
		if (f == NULL) {
			printf("Unable to open %s\n", fname);
			printf("Press Enter to continue...");
			FFLUSH;

			system("cls"); continue;
		}
		break;
	}

	load_text(num_line, line, f);
}

void load_text(int* num_line, char* line[], FILE* f) {
	char wordwrap[WIDTH + 1];
	char first_letter;
	int i = 0, lidx = 0, widx = 0, loop;
	int newword_idx = 0;
	int newline_start;
	int eof = 0;
	
	while (1) {
		if (i > 1000) {
			printf("TOO LONGGGGG\n");
			exit(1);
		}
		
		line[i] = (char*)calloc(WIDTH + 1, sizeof(char));
		line[i][WIDTH] = '\0';

		fscanf(f, "%c", &line[i][0]);

		if (i == 0) {
			newline_start = 1;
		}

		else {
			if (line[i - 1][WIDTH - 1] == ' ')
				newline_start = 1;
			else if (line[i][0] == '\n') {
				line[i][1] = '\0';
				i++;
				continue;
			}
			else if (line[i][0] == ' ')
				newline_start = 1;
			else if (line[i][0] == '\0')
				break;
			else {
				if (widx >= WIDTH) {
					/*for (loop = 0; loop < WIDTH + 1; loop++)
						wordwrap[loop] = '\0';*/

					widx = 0;
					newword_idx = 0;
					newline_start = 1;
				}
				else {
					first_letter = line[i][0];

					strcpy(line[i], line[i - 1] + newword_idx);
					line[i][widx] = first_letter;
					line[i - 1][newword_idx] = '\0';
					newline_start = widx + 1;
					
					newword_idx = 0;
				}
			}
		}
		/*if (i == 42) {
			eof = 0;
		}*/
		for (lidx = newline_start; lidx < WIDTH; lidx++) {
			if (fscanf(f, "%c", &line[i][lidx]) == EOF) {
				line[i][lidx + 1] = '\0';
				eof = 1;
				break;
			}
			// wordwrap[widx] = line[i][lidx];
			widx++;
			if (line[i][lidx] == ' ') {
				newword_idx = lidx + 1;
				widx = 0;
			}

			else if (line[i][lidx] == '\n') {
				line[i][lidx] = '\0';
				newword_idx = 0;
				widx = 0;
				break;
			}
		}
		i++;
		if (eof) break;
	}

	*num_line = i;
	fclose(f);

}

void reader(char* article[], int *num_line) {
	int i;
	int start = 0, end = PAGE_HEIGHT;
	char cmd;
	char fname[30];
	FILE *f;

	while (1) {
		system("cls");
		
		if (end > *num_line - 1) end = *num_line - 1;
		for (i = start; i < end; i++) {
			printf("%s\n", article[i]);
		}
		printf("=======================================================[%d, %d]\n", start + 1, end);
		printf("f, b, o, q>");
		scanf("%c", &cmd); FFLUSH;

		switch (cmd) {
		case 'f':
			if (start > *num_line - PAGE_HEIGHT) continue;
			start += PAGE_HEIGHT;
			end = start + PAGE_HEIGHT;
			break;
		case 'b':
			if (start < PAGE_HEIGHT) continue;
			start -= PAGE_HEIGHT; end = start + PAGE_HEIGHT;
			break;
		case 'o':
			printf("filename: ");
			scanf("%s", fname); FFLUSH;

			f = fopen(fname, "r");
			if (f == NULL) {
				printf("Unable to open %s\n", fname);
				printf("Press Enter to continue...");
				FFLUSH;

				system("cls"); continue;
			}
			else {
				for (i = 0; i < *num_line - 1; i++)
					free(article[i]);
			}
			load_text(num_line, article, f);
			start = 0; end = PAGE_HEIGHT;
			break;
		case 'q':
			for (i = 0; i < *num_line - 1; i++)
				free(article[i]);
			return;
			break;
		default:
			continue;
		}
	}
}