#ifndef LIST_H
#define LIST_H

typedef struct Menu {
	int chicken;
	int beer;
} MENU;

typedef struct Person {
	char* name;
	char* phone;
	struct Person* next;
} PERSON;

typedef struct Table {
	int table_id;
	struct Menu menu;
	struct Person* people;
	struct Table* next;
} TABLE;

TABLE* add_table(TABLE** phead, int table_id);
PERSON* add_person(TABLE* table, char* name, char* phone);
TABLE* find_table(TABLE* head, int table_id);
TABLE* find_person(PERSON* head, char* name);
void remove_table(TABLE** phead, int table_id);
void remove_person(PERSON** phead, char* name);

#endif
