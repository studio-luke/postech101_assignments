#include "utils.h"
#include "list.h"
#include "macro.h"

void enter(TABLE** ptables, FILE* record) {
	char yorn;
	char name[NAME_MAX_LEN], phone[PHONE_MAX_LEN];
	int table_id;
	TABLE* table;
	PERSON* person;

	while (1) {
		printf("마스크를 착용하셨나요? (y/n) ");
		scanf("%c", &yorn); FFLUSH;
		if (yorn == 'y' || yorn == 'Y') {
			printf("이름을 입력해주세요. (20자 이내) >> ");
			scanf("%s", name); FFLUSH;
			printf("전화번호를 입력해주세요. (-없이 11자) >> ");
			scanf("%s", phone); FFLUSH;
			printf("몇 번 테이블에 앉으시겠습니까? >> ");
			scanf("%d", &table_id); FFLUSH;
			table = find_table(*ptables, table_id);
			if (table == NULL) {
				table = add_table(ptables, table_id);
			}
			person = add_person(table, name, phone);
			write_record(record, person, "In");
			show(*ptables);
			break;
		}
		else if (yorn == 'n' || yorn == 'N') {
			print_mask_emoji();
			break;
		}
		else
			printf("입력한 값이 유효하지 않습니다.\n");
	}
}

void show_table(TABLE* table) {
	int cnt = 0;
	PERSON* person;

	printf("\n-----------------------------------\n");
	printf("테이블 ID: %d\n", table->table_id);
	printf("치킨 %d 마리\n", table->menu.chicken);
	printf("생맥주 %d 잔\n", table->menu.beer);
	for (person = table->people; person != NULL; person = person->next)
		printf("손님 [%d] 이름: %s\n", cnt++, person->name);
	printf("-----------------------------------\n");
}

void show(TABLE* tables) {
	TABLE* table;
	if (tables == NULL) {
		printf("손님이 있는 테이블이 없습니다.\n");
		return;
	}

	for (table = tables; table != NULL; table = table->next) {
		show_table(table);
	}
}

void order(TABLE* tables) {
	TABLE* table;
	char order[ORDER_CODE_MAX_LEN];
	char* each_order;
	int beer = 0, chicken = 0, order_amount;

	if ((table = user_find_table(tables)) == NULL)
		return;

	printf("\n주문 코드를 입력해주세요.\n");
	printf("주문 예1) 치킨 10마리: c10\n");
	printf("주문 예2) 생맥주 2잔: b2\n");
	printf("주문 예3) 치킨 2마리, 생맥주 1잔: c2 b1\n");
	printf(" >> ");
	fgets(order, ORDER_CODE_MAX_LEN, stdin);

	each_order = strtok(order, " ");
	while (each_order != NULL) {
		order_amount = atoi(each_order + 1);
		if (strchr(each_order + 1, '.') != NULL) // Float input error
			order_amount = -1;

		switch (each_order[0]) {
		case 'b':
		case 'c':
			if (order_amount <= 0) {
				printf("입력한 숫자 코드가 유효하지 않습니다.\n");
				return;
			}
			break;
		default:
			printf("음식 코드는 {치킨:c, 생맥주:c}만 가능합니다.\n");
			return;
		}

		if (each_order[0] == 'b') beer += order_amount;
		else chicken += order_amount;
		each_order = strtok(NULL, " ");
	}
	
	table->menu.beer += beer;
	table->menu.chicken += chicken;
	show_table(table);
}

void leave(TABLE** ptables, FILE* record) {
	TABLE* table;
	PERSON* person;
	char name[NAME_MAX_LEN];

	if ((table = user_find_table(*ptables)) == NULL)
		return;

	printf("이름을 입력해주세요. (20자 이내) >> ");
	scanf("%s", name); FFLUSH;
	if ((person = find_person(table->people, name)) == NULL) {
		printf("%d번 테이블에 %s씨는 없습니다.\n", table->table_id, name);
		return;
	}

	write_record(record, person, "Out");
	remove_person(&table->people, name);
	if (table->people == NULL)
		remove_table(ptables, table->table_id);
	show(*ptables);
}

void quit(TABLE* tables, FILE* record) {
	TABLE* table, * next_table;
	PERSON* person, * next_person;

	for (table = tables; table != NULL; table = next_table) {
		for (person = table->people; person != NULL; person = next_person) {
			write_record(record, person, "Out");
			free(person->name);
			free(person->phone);
			next_person = person->next;
			free(person);
		}
		next_table = table->next;
		free(table);
	}
	fclose(record);
	printf("영업을 종료합니다. 남아있던 손님들도 퇴장하여 출입 명부에 기록합니다.\n");
	printf("치킨 먹고 건강하세요~\n\n");
}


TABLE* user_find_table(TABLE* tables) {
	int table_id;
	TABLE* table;

	if (tables == NULL) {
		printf("손님이 있는 테이블이 없습니다.\n");
		return NULL;
	}

	printf("테이블 번호를 입력해주세요. >> ");
	scanf("%d", &table_id); FFLUSH;
	table = find_table(tables, table_id);
	if (table == NULL) {
		printf("%d번 테이블은 없습니다.\n", table_id);
		return NULL;
	}
}

void get_current_time(char* time_string) {
	time_t current_time;
	char* new_line_pos;

	current_time = time(NULL);
	ctime_s(time_string, TIME_MAX_LEN, &current_time);

	if ((new_line_pos = strchr(time_string, '\n')) != NULL)
		*new_line_pos = '\0';
}

void write_record(FILE* record, PERSON* p, char* in_or_out) {
	char cur_time[TIME_MAX_LEN];
	get_current_time(cur_time);
	fprintf(record, "[%s]\t\t%s\t%s\t%s\n", cur_time, in_or_out, p->name, p->phone);
}

void print_mask_emoji() {
	printf("                         `-,:~<*r)|vvvvv|)r*<=:,-` \n");
	printf("                     .,=*?vvvvvvvvvvvvvvvvvvvvvvvv*=,. \n"); 
	printf("                 `_~rvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvr~_` \n");
	printf("              `_~?vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv?~_` \n");
	printf("            '!\vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv|>` \n");
	printf("          `=)vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv?=` \n");
	printf("         `:)vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv):` \n");
	printf("        .*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*- \n");
	printf("      `!vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv!` \n");
	printf("     `~vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv~` \n");
	printf("    `~vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvxvvvvvvvvvvvvvvvvvvvvvvvv>` \n");
	printf("    !vvvvvvvvvvvvvvvY@@@@@B##vvvvvvvvvvvvvvvvvvvvv@@@@@@vvvvvvvvvvvvvvvv! \n");
	printf("   :vvvvvvvvvvv}K@@@@@@@@@@@@#vvvvvvvvvvvvvvVQ@@@@@@@@@@@@B9m}vvvvvvvvvvv: \n");
	printf("  `rvvvvvvvvvvK@@@@@BBgdPB@@@@@vvvvvvvvvvvvvv@@@@VXPdgB@@@@@@Evvvvvvvvvvvr`\n");
	printf(" :vvvvvvvvvvv@@@@dIYvvvvvv@@@@@vvvvvvvvvvvv#@@@vvvvvvvv}U@@@Rvvvvvvvvvvvv:\n");
	printf("<vvvvvvvvvvvv]ivvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvi]vvvvvvvvvvvv<\n");
	printf("._!^)vvvvvvvvvvvvvvvv?)))))))))))))))))))))))))))))|vvvvvvvvvvvvvvvv)^!_.\n");
	printf("`````-:~rvvvvvvvvv|=-```````````````````````````````-~|vvvvvvvvvr~:-`````\n");
	printf("*~:-`````.,=*vvvvv:```````````````````````````````````:vvvvvr=,.`````-:~*\n");
	printf(")vvvr<:_'````.,=*)_```````````````````````````````````,)^!,.`````_:<rvvv)\n");
	printf("^vvvvvvvv)^!_```````````````````````````````````````````````-!^)vvvvvvvv^\n");
	printf(":vvvvvvvvvvvv)^!,'`````````````````````````````````````.,!^)vvvvvvvvvvvv:\n");
	printf("`rvvvvvvvvvvvvvvv\\_```````````````````````````````````_|vvvvvvvvvvvvvvvr`\n");
	printf(" \"vvvvvvvvvvvvvvvv_```````````````````````````````````_vvvvvvvvvvvvvvvv\" \n");
	printf("  !vvvvvvvvvvvvvvv_```````````````````````````````````_vvvvvvvvvvvvvvv! \n");
	printf("  `_\":=~^*r|vvvvvv_```````````````````````````````````_vvvvvv|r*^~!:\"_` \n");
	printf("    ````````.-,:!=.```````````````````````````````````.=!:,-.```````` \n");
	printf("     `,_-'`````````````````````````````````````````````````````'-_,` \n");
	printf("      .*vvv\\)*^~=:' ``````````````````````````````````.:=~^*)\vvv*. \n");
	printf("       `:)vvvvvvvv_```````````````````````````````````_vvvvvvvv):` \n");
	printf("         `=?vvvvvv:```````````````````````````````````:vvvvvv?=` \n");
	printf("           `!|vvvv?!-```````````````````````````````-!?vvvv|>` \n");
	printf("             `_~)vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv?~_` \n");
	printf("                `_~rvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvr~_` \n");
	printf("                    .,=*?vvvvvvvvvvvvvvvvvvvvvvv\\*=,. \n");
	printf("                        `-,:=<*r)?vvvvv?)r*<=:,-` \n");
	printf("********************마스크 착용 후 입장 부탁드립니다.******************\n");
}