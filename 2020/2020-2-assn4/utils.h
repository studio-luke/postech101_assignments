#ifndef UTILS_H
#define UTILS_H

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FFLUSH while(getchar()!='\n');

void enter(TABLE **ptables, FILE* record);
void show(TABLE * tables);
void order(TABLE * tables);
void leave(TABLE * *ptables, FILE * record);
void quit(TABLE * tables, FILE * record);
TABLE* user_find_table(TABLE * tables);
void get_current_time(char* time_string);
void write_record(FILE * record, PERSON * p, char* in_or_out);
void print_mask_emoji();

#endif