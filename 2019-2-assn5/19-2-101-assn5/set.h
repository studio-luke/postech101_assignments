#pragma once

typedef struct ele 
{ 
	int data;  
	struct ele* next; 
} Element;

typedef struct set 
{ 
	char set_name[21];
	int set_size;
	Element* ele_head;
	struct set* next;
} Set;

typedef struct setlist
{
	Set* head;
	Set* tail;
	int count;
} SetList;

int set_init(SetList* S, char* params);
void set_add(Set* s, int e);
void set_show(Set* S);
int set_is_elem(Set* s, int e);
void set_pop(Set* s, int e);

void set_ud(Set* A, char op, Set* B, char* newset_name, SetList* S);
void set_inter(Set* A, Set* B, char* newset_name, SetList* S);
int set_is_disjoint(Set* A, Set* B, SetList* S);
int set_is_subset(Set* small, Set* big, SetList* S);

void setlist_add(SetList* S, Set* v);
/* if setname is NULL, remove head elemnet */
void setlist_remove(SetList* S, char* setname);
Set* find_set(SetList* S, char* name);

/* return 0 if no error occurs, otherwise return 1 */
int safe_atoi_assign(int* dst, char* s);

/* return 0 if no error occurs, otherwise return 1 */
int Strtok_wrapper(char** dst, char* str, char* delim, char* err_msg); 

#define DELIM " \n\t"
#define MAX_CMDLEN 100
#define MAX_PARAMS 16
#define FFLUSH while(getchar() != '\n')
