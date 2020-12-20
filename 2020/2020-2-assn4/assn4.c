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
		printf("System Error: %s ������ ��������� �� �� �����ϴ�.\n", FILENAME);
		return 100;
	}
	fprintf(record, "[�ð�]\t\t\t\t����\t�̸�\t��ȭ��ȣ\n");
	printf("�������. �濪 ġŲ�Դϴ�.\n");

	while (1) {
		printf("\n��ɾ �Է��ϼ���. >> ");
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
			printf("�� �� ���� ��ɾ��Դϴ�.\n\n");
		}
	}
}