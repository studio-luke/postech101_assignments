// Started at 13:06, 07/08/2020
// Code by studio-luke

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FFLUSH while(getchar() != '\n')

typedef struct student {
	int sid;
	char name[31];
	int mid;
	int fin;
	float avg;
	char grade;
} STU;

typedef struct node {
	STU dat;
	struct node* next;
} NODE;

char lower(char c) {
	return ('A' <= c && c <= 'Z') ? c - 'A' + 'a' : c;
}

void lower_string(char* c) {
	for (int i = 0; c[i] != '\0'; i++)
		c[i] = lower(c[i]);
}

void insert_data(NODE* head, STU dat) {
	NODE* prev;
	NODE* top = head->next;

	NODE* newnode = malloc(sizeof(NODE));
	newnode->dat = dat;

	if (top == NULL || dat.avg > top->dat.avg) { // insert to head
		newnode->next = top;
		head->next = newnode;
	}
	else {
		for (prev = top; prev->next != NULL; prev = prev->next)
			if (dat.avg > prev->next->dat.avg) break;
		newnode->next = prev->next;
		prev->next = newnode;
	}
}

//void swap_adjacent_node(NODE* head, NODE* first) {
//	STU dat = first->next->dat;
//
//	delete_node(head, first);
//
//	for (NODE* tmp = head; tmp->next != NULL; tmp = tmp->next) 
//		if (tmp->next == first) {
//			NODE* swapped = malloc(sizeof(NODE));
//			swapped->dat = dat;
//			swapped->next = first;
//			tmp->next = swapped;
//			break;
//		}
//}

NODE* search_sid_prev(NODE* head, int sid) {
	NODE *look, *prev;
	for (look = head->next, prev = head; look != NULL; look = look->next) {
		if (look->dat.sid == sid) 
			return prev;
		prev = look;
	}
}

int delete_node(NODE* head, NODE* prev) {
	NODE* del;
	
	if (prev == NULL || prev->next == NULL) return 0; // Fail to delete
	del = prev->next;
	prev->next = del->next;
	free(del);
	return 1; // Success to delete
}

char cal_grade(float score) {
	int scale = min((int)score / 10, 9);
	switch (scale) {
	case 9: return 'A';
	case 8: return 'B';
	case 7: return 'C';
	case 6: return 'D';
	default: return 'F';
	}
}

void complete_stu_data(STU* pstu, char* family, char* given) {
	if (family && given) {
		strcpy(pstu->name, family);
		strcat(pstu->name, " ");
		strcat(pstu->name, given);
	}
	pstu->avg = (pstu->mid + pstu->fin) / 2.0;
	pstu->grade = cal_grade(pstu->avg);
}

int read_score(FILE* f, NODE* head) {
	STU input;
	int eofcheck = 0;
	char family[30], given[30];
	while (1) {
		eofcheck = fscanf(f, "%d  %s  %s  %d  %d",
			&input.sid, family, given, &input.mid, &input.fin);
		if (eofcheck == EOF) break;
		complete_stu_data(&input, family, given);
		insert_data(head, input);
	}
}

void print_categories() {
	printf("\nStudent\t\t\t\tName\tMidterm\tFinal\tAverage\tGrade\n");
	printf("---------------------------------------------------------------------\n");
}

void print_stu(STU s) {
	printf("%d%30s\t%d\t%d\t%.1f\t%c\n",
		s.sid, s.name, s.mid, s.fin, s.avg, s.grade);
}

void print_all(NODE* head) {
	print_categories();
	for (NODE* look = head->next; look != NULL; look = look->next)
		print_stu(look->dat);
}

NODE* find_student_by_sid(NODE* head, int* psid) {
	NODE* prev;

	printf("Student ID: ");
	scanf("%d", psid); FFLUSH;
	prev = search_sid_prev(head, *psid);
	if (prev->next == NULL) 
		return NULL;
	return prev;
}


int valid_score() {
	int score;
	while (1) {
		scanf("%d", &score); FFLUSH;
		if (score < 0 || score > 100)
			printf("INVALID SCORE - please retype: ");
		else return score;
	}
}

void change_student_score(NODE* head, NODE* prev) {
	char input[31];
	int newscore;
	int is_mid;
	STU s;

	printf("Mid/Final?: ");
	scanf("%s", input); FFLUSH;
	if (!strcmp(input, "mid"))
		is_mid = 1;
	else if (!strcmp(input, "final"))
		is_mid = 0;
	else {
		printf("WRONG INPUT\n");
		return;
	}
	printf("Input new score: ");
	newscore = valid_score();
	
	s = prev->next->dat;
	print_categories();
	print_stu(s);

	if (is_mid) s.mid = newscore;
	else s.fin = newscore;
	complete_stu_data(&s, NULL, NULL);
	printf("Score changed\n");
	print_stu(s);

	delete_node(head, prev);
	insert_data(head, s);
}

void show_students_by_grade(NODE* head) {
	char grade;
	int found = 0;
	NODE* look;

	printf("Grade to search: ");
	scanf("%c", &grade); FFLUSH;
	switch (grade) {
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'F': break;
	default: printf("WRONG INPUT\n");
		return;
	}
	
	print_categories();
	for (look = head->next; look != NULL; look = look->next) {
		if (look->dat.grade == grade) {
			found = 1;
			print_stu(look->dat);
		}
	}
	if (!found)
		printf("NO RESULT\n");

}


void add_student(NODE* head, int sid) {
	STU s;
	char family[30], given[30];

	s.sid = sid;
	printf("Name: ");
	scanf("%s%s", family, given); FFLUSH;

	printf("Midterm Score: ");
	s.mid = valid_score();
	printf("Final Score: ");
	s.fin = valid_score();
	complete_stu_data(&s, family, given);

	insert_data(head, s);
	printf("Student added\n");
}

void write_file(NODE* head) {
	char fname[31];
	FILE *outfile;
	printf("File name: ");
	scanf("%s", fname); FFLUSH;
	outfile = fopen(fname, "w");

	for (NODE* look = head->next; look != NULL; look = look->next)
		fprintf(outfile, "%d\t%s\t%d\t%d\n",
			look->dat.sid, look->dat.name, look->dat.mid, look->dat.fin);
	fclose(outfile);
}

int main()
{	
	char fname[31] = "", cmd[31] = "";
	FILE *infile;
	NODE *head = calloc(1, sizeof(NODE)); // EMPTY NULL HEAD
	NODE *prev;
	int sid;
	char input;

	printf("Input the score file name: ");
	scanf("%s", fname); FFLUSH;

	if ((infile = fopen(fname, "r")) == NULL) {
		printf("Could not open %s file\n", fname);
		free(head);
		return 1;
	}

	read_score(infile, head);
	fclose(infile);
	
	print_all(head);

	while (1) {
		printf("\n# ");
		scanf("%s", cmd); FFLUSH;
		lower_string(cmd);

		if (!strcmp(cmd, "show")) {
			print_all(head);
		}
		else if (!strcmp(cmd, "search")) {
			if (prev = find_student_by_sid(head, &sid)) {
				print_categories();
				print_stu(prev->next->dat);
			}
		}
		else if (!strcmp(cmd, "changescore")) {
			if (prev = find_student_by_sid(head, &sid))
				change_student_score(head, prev);
			else
				printf("NO SUCH PERSON\n");
		}
		else if (!strcmp(cmd, "searchgrade")) {
			show_students_by_grade(head);
		}
		else if (!strcmp(cmd, "add")) {
			if (prev = find_student_by_sid(head, &sid))
				printf("ALREADY EXISTS\n");
			else {
				add_student(head, sid);
			}
		}
		else if (!strcmp(cmd, "remove")) {
			if (head && head->next == NULL)
				printf("LIST IS EMPTY");
			else if (prev = find_student_by_sid(head, &sid)) {
				print_categories();
				print_stu(prev->next->dat);
				printf("\nRemove %d (y/n)? ", prev->next->dat.sid);
				scanf("%c", &input); FFLUSH;
				if (lower(input) == 'y') {
					delete_node(head, prev);
					printf("Student removed\n");
				}
			}
			else
				printf("NO SUCH PERSON\n");
		}
		else if (!strcmp(cmd, "quit")) {
			printf("Save data(y/n)? ");
			scanf("%c", &input); FFLUSH;
			if (lower(input) == 'y')
				write_file(head);

			while (delete_node(head, head)); // delete top
			free(head);
			break;
		}
		else
			printf("WRONG INPUT\n");
	}
}