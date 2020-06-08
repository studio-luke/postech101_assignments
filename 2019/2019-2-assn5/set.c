#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

/* ======================================================
				       Set functions
   ======================================================*/

int set_init(SetList* S, char* params) {
	char* token;
	Set* newset;
	int set_size, cnt = 0;
		
	newset = calloc(1, sizeof(Set));
	newset->ele_head = NULL;
	newset->set_size = 0;
	
	/* Getting Set size */
	if (Strtok_wrapper(&token, params, DELIM, "set name needed")) {
		free(newset);
		return 1;
	}

	if (find_set(S, token)) {
		printf("Error: Set name already exists\n");
		free(newset);
		return 1;
	}
	strcpy(newset->set_name, token);

	/* Getting set size */
	if (Strtok_wrapper(&token, NULL, DELIM, "set size needed")) {
		free(newset);
		return 1;
	}

	if (safe_atoi_assign(&set_size, token)) {
		printf("Error: Invalid set size\n");
		free(newset);
		return 1;
	}

	while ((token = strtok(NULL, DELIM)) != NULL) {
		set_add(newset, atoi(token)); cnt++;
	}
	setlist_add(S, newset);

	if (set_size != cnt) {
		printf("Set size incorrect!\n");
		setlist_remove(S, NULL);
		return 1;
	}
	return 0;
}

void set_add(Set* s, int e) {
	Element* hold;
	Element* elem, *prev_elem = NULL;
	
	if (set_is_elem(s, e)) return;

	elem = malloc(sizeof(Element));
	elem->data = e;
	elem->next = NULL;

	if (s->ele_head == NULL) {
		s->ele_head = elem;
	}
	else {
		for (hold = s->ele_head; hold != NULL; hold = hold->next) {
			if (e < hold->data) {
				elem->next = hold;
				break;
			}
			prev_elem = hold;
		}

		if (prev_elem == NULL)
			s->ele_head = elem;
		else
			prev_elem->next = elem;
	}
	s->set_size += 1;
}

void set_show(Set* S) {
	Element *elem;

	printf("%s : ", S->set_name);
	for (elem = S->ele_head; elem != NULL; elem = elem->next)
		printf("%d ", elem->data);
	printf("\n");
}

int set_is_elem(Set* s, int e) {
	Element* hold;

	for (hold = s->ele_head; hold != NULL; hold = hold->next)
		if (hold->data == e)
			return 1;
	return 0;
}

void set_pop(Set* s, int e) {
	Element* tar, * prev_elem = NULL;

	if (!set_is_elem(s, e)) return;
	if (s->ele_head == NULL) return;

	for (tar = s->ele_head; tar != NULL; tar = tar->next) {
		if (e == tar->data) {
			break;
		}
		prev_elem = tar;
	}

	if (tar == s->ele_head) {
		s->ele_head = s->ele_head->next;
	}
	else {
		prev_elem->next = tar->next;
	}
	free(tar);
	s->set_size -= 1;
}


/* ======================================================
					   Set Operations
   ======================================================*/

void set_cpy(Set* dst, Set* src) {
	Element* hold;

	if (dst->set_size > 0) {
		printf("Rule violation: Dst Set should be empty\n");
		return;
	}

	for (hold = src->ele_head; hold != NULL; hold = hold->next) {
		set_add(dst, hold->data);
	}
	if (dst->set_size != src->set_size) {
		printf("FATAL WARNING: Set copy error\n");
	}
}

void set_ud(Set* A, char op, Set* B, char* newset_name, SetList* S) {
	char *buf = malloc(sizeof(char) * (strlen(newset_name) + 3));
	Set* newset;
	Element* hold;

	sprintf(buf, "%s 0", newset_name);

	if (set_init(S, buf)) return;

	newset = find_set(S, newset_name);

	set_cpy(newset, A);
	for (hold = B->ele_head; hold != NULL; hold = hold->next) {
		if (op == '+')
			set_add(newset, hold->data);
		else if (op == '-')
			set_pop(newset, hold->data);
	}

	free(buf);
}

void set_inter(Set* A, Set* B, char* newset_name, SetList* S) {
	char* tmp = "__tmp__";
	Set* A_minus_B;

	set_ud(A, '-', B, tmp, S);
	A_minus_B = find_set(S, tmp);

	set_ud(A, '-', A_minus_B, newset_name, S);
	
	setlist_remove(S, tmp);
}

int set_is_disjoint(Set* A, Set* B, SetList* S) {
	char* tmp = "__tmp_dsj__";
	Set* A_inter_B;
	int is_disjoint;

	set_inter(A, B, tmp, S);
	A_inter_B = find_set(S, tmp);

	is_disjoint = (A_inter_B->set_size == 0);

	setlist_remove(S, tmp);
	return is_disjoint;
}

int set_is_subset(Set* small, Set* big, SetList* S) {
	int is_subset;
	char* tmp = "__tmp_subs__";
	Set* A_diff_B;

	set_ud(small, '-', big, tmp, S);
	A_diff_B = find_set(S, tmp);
	is_subset = (A_diff_B->set_size == 0);

	setlist_remove(S, tmp);
	return is_subset;


}


/* ======================================================
                      SetList functions
   ======================================================*/

Set* find_set(SetList* S, char* name) {
	Set* tmp = S->head;

	while (tmp != NULL) {
		if (!strcmp(tmp->set_name, name))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void setlist_add(SetList* S, Set* v) {
	if (S->head == NULL) {
		S->head = S->tail = v;
	}
	else {  // Add tail
		S->tail->next = v;
		S->tail = v;
	}

	S->count += 1;
}

void setlist_remove(SetList* S, char* setname) {
	int i;

	Set* tar_set, *prev_set, *tmp;
	Element* hold, *tar_ele;


	if (setname == NULL) { // Remove tail
		tar_set = S->tail;
		if (S->count <= 1) {
			S->tail = NULL;
			S->head = NULL;
		}

		else {
			for (tmp = S->head; tmp->next != S->tail; tmp = tmp->next);
			S->tail = tmp;
			S->tail->next = NULL;
		}
	}
	else {
		prev_set = NULL;
		for (tar_set = S->head; !!strcmp(setname, tar_set->set_name); tar_set = tar_set->next) {
			prev_set = tar_set;
		}

		if (tar_set == S->head) {
			S->head = tar_set->next;
		}
		else {
			if (tar_set->next == NULL)  // if (prev_set == tail)
				S->tail = prev_set;
			prev_set->next = tar_set->next;
		}
	}
	
	/* Free all the elements of the target set */
	hold = tar_set->ele_head;
	for (i = 0; i < tar_set->set_size; i++) {
		tar_ele = hold;
		hold = hold->next;
		free(tar_ele);
	}
	free(tar_set); 

	S->count -= 1;
}