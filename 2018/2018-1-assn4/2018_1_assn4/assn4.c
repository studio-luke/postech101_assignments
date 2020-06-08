
#include "stdafx.h"

#define ERR_OUT stdout

int main()
{
	char ifname[32], ofname[32];
	char query[32], command[10];
	VAR* var;
	int var_num = 0;
	int par_num;
	char var_name, *tmpstr;
	int i;
	FILE *inf, *outf;

	while (1) {
		printf("Enter input file <default = stdin>: ");
		gets(ifname);
		if (ifname[0] == '\0')
			inf = stdin;
		else {
			inf = fopen(ifname, "r");
			if (inf == NULL) {
				fprintf(ERR_OUT, "Incorrect File Name Entered.\n");
				continue;
			}
		}

		printf("Enter onput file <default = stdout>: ");
		gets(ofname);
		if (ofname[0] == '\0')
			outf = stdout;
		else {
			outf = fopen(ofname, "w");
			if (outf == NULL) {
				fprintf(ERR_OUT, "Incorrect File Name Entered.\n");
				continue;
			}
		}
		break;
	}
	while (1) {
		printf(">>> ");
		fgets(query, 32, inf);
		
		for (i = 0; i < strlen(query); i++) {

		}

		strcpy(command, strtok(query, " "));
		//if (strstr(command))
		if (strcmp(command, "USE") == 0) {
			if (var_num > 0) {
				fprintf(ERR_OUT, "The command USE is already used\n");
				continue;
			}
			tmpstr = strtok(NULL, " ");
			var_num = atoi(tmpstr);
			if (var_num == 0) {
				fprintf(ERR_OUT, "Unexpected parameters.\n");
				continue;
			}
			if (strstr(tmpstr, "\n"));
			else if (strcmp(strtok(NULL, " "), "\n") != 0) {
				fprintf(ERR_OUT, "Too much parameters.\n");
				var_num = 0;
				continue;
			}
			cmd_use(&var, var_num);
		}
		else {
			if (var_num == 0) {
				fprintf(ERR_OUT, "The first command should be always USE n.\n");
				continue;
			}

			if (strcmp(command, "END") == 0) {
				free(var);
				return 0;
			}
			else if (strcmp(command, "VECTOR") == 0) {
				tmpstr = strtok(NULL, " ");
				if (tmpstr[1] != '\0') {
					fprintf(ERR_OUT, "Improper variable Name.\n");
					continue;
				}
				var_name = tmpstr[0];

				par_num = atoi(strtok(NULL, " "));

			}
			else {
				fprintf(ERR_OUT, "Incorrect command entered.\n");
			}
		}
	}
	
}