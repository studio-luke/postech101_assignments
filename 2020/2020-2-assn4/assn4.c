// Started on 20:49 12/05/2020
// Code by Studio-Luke

#include "utils.h"
#include "list.h"
#include "macro.h"


int main() {
	char cmd[COMMAND_MAX_LEN];
	TABLE* tables = NULL;
	FILE* record;

	record = fopen(FILENAME, "w");
	if (record == NULL) {
		printf("System Error: %s 파일을 쓰기용으로 열 수 없습니다.\n", FILENAME);
		return 100;
	}
	fprintf(record, "[시간]\t\t\t\t출입\t이름\t전화번호\n");
	printf("어서오세요. 방역 치킨입니다.\n");

	while (1) {
		printf("\n명령어를 입력하세요. >> ");
		fgets(cmd, COMMAND_MAX_LEN, stdin);
		cmd[strcspn(cmd, "\n")] = '\0';

		if (!strcmp(cmd, "enter")) {
			enter(&tables, record);
		}
		else if (!strcmp(cmd, "show")) {
			show(tables);
		}
		else if (!strcmp(cmd, "order")) {
			order(tables);
		}
		else if (!strcmp(cmd, "leave")) {
			leave(&tables, record);
		}
		else if (!strcmp(cmd, "quit")) {
			quit(tables, record);
			printf("Press Enter to Continue.. ");
			getchar();
			return 0;
		}
		else if (!strcmp(cmd, ""))
			continue;
		else {
			printf("알 수 없는 명령어입니다.\n\n");
		}
	}
}