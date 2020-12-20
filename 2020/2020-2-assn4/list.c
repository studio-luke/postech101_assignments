#include "list.h"
#include "utils.h"

// Create a new table with given ID, then return address of the new table
TABLE* add_table(TABLE** phead, int table_id) {
	TABLE* head = *phead;
	TABLE* tmp;
	TABLE* newtable = malloc(sizeof(TABLE));
	MENU nomenu = { 0, 0 };

	if (newtable == NULL) {
		printf("FATAL ERROR: cannot allocate new memory!!\n");
		exit(1);
	}
	newtable->table_id = table_id;
	newtable->people = NULL;
	newtable->menu = nomenu;

	if (head == NULL || table_id < head->table_id) {
		newtable->next = head;
		(*phead) = newtable;
	}
	else {
		for (tmp = head; tmp->next != NULL; tmp = tmp->next)
			if (table_id <= head->next->table_id)
				break;
		newtable->next = tmp->next;
		tmp->next = newtable;
	}

	return newtable;
}

// Add a new person to the table given
PERSON* add_person(TABLE* table, char* name, char* phone) {
	PERSON* newperson = malloc(sizeof(PERSON));
	PERSON* head = table->people;
	PERSON* tmp;

	if (newperson == NULL) {
		printf("FATAL ERROR: cannot allocate new memory!!\n");
		exit(2);
	}

	newperson->name = malloc((strlen(name) + 1) * sizeof(char));
	if (newperson->name == NULL) {
		printf("FATAL ERROR: cannot allocate new memory!!\n");
		exit(3);
	}
	strcpy(newperson->name, name);
	
	newperson->phone = malloc((strlen(phone) + 1) * sizeof(char));
	if (newperson->name == NULL) {
		printf("FATAL ERROR: cannot allocate new memory!!\n");
		exit(4);
	}
	strcpy(newperson->phone, phone);
	
	if (head == NULL || strcmp(name, head->name) == -1) {
		newperson->next = head;
		table->people = newperson;
	}
	else {
		for (tmp = head; tmp->next != NULL; tmp = tmp->next)
			if (strcmp(name, tmp->next->name) == -1)
				break;
		newperson->next = tmp->next;
		tmp->next = newperson;
	}
	return newperson;
}

void remove_table(TABLE** phead, int table_id) {
	TABLE* head = *phead;
	TABLE* prev, *to_delete;

	if (head->table_id == table_id) {
		to_delete = head;
		*phead = head->next;
		free(to_delete);
	}
	else {
		for (prev = head; prev->next != NULL; prev = prev->next)
			if (prev->next->table_id == table_id)
				break;
		to_delete = prev->next;
		if (to_delete == NULL) {
			printf("%d번 테이블이 존재하지 않아 삭제할 수 없습니다.\n", table_id);
			return;
		}
		if (to_delete->people != NULL) {
			printf("테이블에 사람이 있어 삭제할 수 없습니다.\n");
			return;
		}
		prev->next = to_delete->next;
		free(to_delete);
	}
}

void remove_person(PERSON** phead, char* name) {
	PERSON* head = *phead;
	PERSON* prev, *to_delete;

	if (!strcmp(head->name, name)) {
		to_delete = head;
		*phead = head->next;
		free(to_delete);
	}
	else {
		for (prev = head; prev->next != NULL; prev = prev->next)
			if (!strcmp(prev->next->name, name))
				break;
		to_delete = prev->next;
		if (to_delete == NULL) {
			printf("%s씨가 존재하지 않아 삭제할 수 없습니다.\n", name);
			return;
		}
		
		free(to_delete->name);
		free(to_delete->phone);
		prev->next = to_delete->next;
		free(to_delete);
	}
}

// Find the table with given ID, if not found, return NULL
TABLE* find_table(TABLE* head, int table_id) {
	for (TABLE* tmp = head; tmp != NULL; tmp = tmp->next) {
		if (tmp->table_id == table_id)
			return tmp;
	}
	return NULL;
}


// Find the person with given name, if not found, return NULL
TABLE* find_person(PERSON* head, char* name) {
	for (PERSON* tmp = head; tmp != NULL; tmp = tmp->next) {
		if (!strcmp(tmp->name, name))
			return tmp;
	}
	return NULL;
}