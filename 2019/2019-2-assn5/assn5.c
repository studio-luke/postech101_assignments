#include <stdio.h>
#include <string.h>
#include "set.h"

int safe_atoi_assign(int* dst, char* s) {
	if ((*dst = atoi(s)) == 0 && !!strcmp(s, "0")) return 1;
	else return 0;
}

int Strtok_wrapper(char** dst, char* str, char* delim, char* err_msg) {
	if ((*dst = strtok(str, delim)) == NULL) {
		if (err_msg)
			printf("Error: %s\n", err_msg);
		return 1;
	}

	return 0;
}

int main(int argc, char** argv) {
	FILE* stream = stdin, * file;
	char cmdline[MAX_CMDLEN], buf[MAX_CMDLEN];
	char* cmd, * params[MAX_PARAMS];
	Set* tar, *tar2;
	int i, num;

	SetList S;
	S.head = S.tail = NULL;
	S.count = 0;

	if (argc > 1) {
		file = fopen(argv[1], "r");
		if (file == NULL)
			printf("[Fatal Error...] Cannot open file\n");
		else
			stream = file;
	}

	while (1) {
		if (stream == stdin)
			printf("\n>> ");
		if (fgets(cmdline, MAX_CMDLEN, stream) == NULL) {
			// printf("end of file.\n");
			stream = stdin;
			continue;
		}
		strcpy(buf, cmdline);

		if (Strtok_wrapper(&cmd, buf, DELIM, NULL)) continue;

		/* 1. SET COMMAND */
		if (!strcmp(cmd, "set")) {
			params[0] = cmd + strlen(cmd) + 1;
			set_init(&S, params[0]);
		}

		/* 2. SHOW COMMAND */
		else if (!strcmp(cmd, "show")) {
			if (Strtok_wrapper(&params[0], NULL, DELIM, NULL)) {  // print all sets
				tar = S.head;
				for (i = 0; i < S.count; i++) {
					set_show(tar);
					tar = tar->next;
				}
				continue;
			}

			if ((tar = find_set(&S, params[0])) == NULL) {
				printf("no matching sets...\n");
				continue;
			}
			set_show(tar);

		}

		/* 7. QUIT COMMAND */
		else if (!strcmp(cmd, "quit")) {
			for (i = 0; i < S.count; i++)
				setlist_remove(&S, NULL);
			printf("\nPress Enter to quit..."); FFLUSH;
			return 0;
		}

		else if (!strcmp(cmd, "is_element") || !strcmp(cmd, "add") ||
			!strcmp(cmd, "pop") || !strcmp(cmd, "clear")) { // Commands that needs set name as the first parameter

			if (Strtok_wrapper(&params[0], NULL, DELIM, "Set name needed"))
				continue;

			if (!strcmp(cmd, "clear")) {
				/* 6. CLEAR COMMAND */
				setlist_remove(&S, params[0]);
			}
			else {
				if (Strtok_wrapper(&params[1], NULL, DELIM, "a number needed"))
					continue;

				if ((tar = find_set(&S, params[0])) == NULL) {
					printf("Error: no matching set '%s'...\n", params[0]);
					continue;
				}

				if (safe_atoi_assign(&num, params[1])) {
					printf("Error: a number needed, received %s\n", params[1]);
					continue;
				}
				/* 3. IS_ELEMENT COMMAND */
				if (!strcmp(cmd, "is_element"))
					printf("%d\n", set_is_elem(tar, num));
				/* 4. ADD COMMAND */
				else if (!strcmp(cmd, "add"))
					set_add(tar, num);
				/* 5. POP COMMAND */
				else if (!strcmp(cmd, "pop")) {
					set_pop(tar, num);
				}
			}
		}
		else if (!strcmp(cmd, "union") || !strcmp(cmd, "intersection") ||
			!strcmp(cmd, "difference") || !strcmp(cmd, "is_disjoint") || !strcmp(cmd, "is_subset")) {
			if (Strtok_wrapper(&params[0], NULL, DELIM, "Set name needed") ||
				Strtok_wrapper(&params[1], NULL, DELIM, "Two set source needed")) continue;

			if ((tar = find_set(&S, params[0])) == NULL) {
				printf("Error: no matching set '%s'...\n", params[0]);
				continue;
			}
			if ((tar2 = find_set(&S, params[1])) == NULL) {
				printf("Error: no matching set '%s'...\n", params[1]);
				continue;
			}
			
			if (!strcmp(cmd, "is_disjoint"))
				printf("%d\n", set_is_disjoint(tar, tar2, &S));
			else if (!strcmp(cmd, "is_subset"))
				printf("%d\n", set_is_subset(tar, tar2, &S));

			else {
				if (Strtok_wrapper(&params[2], NULL, DELIM, "a destination set name needed"))
					continue;

				if (!strcmp(cmd, "union"))
					set_ud(tar, '+', tar2, params[2], &S);
				else if (!strcmp(cmd, "difference"))
					set_ud(tar, '-', tar2, params[2], &S);
				else if (!strcmp(cmd, "intersection"))
					set_inter(tar, tar2, params[2], &S);
			}
		}
		else {
			printf("%s: Command not found\n", cmd);
			continue;
		}// End of command classifier
	} // while
} // main