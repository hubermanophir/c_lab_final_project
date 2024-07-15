#ifndef MACRO_H
#define MACRO_H

#include "../../header_files/data_structures/linked_list.h"
#include <stdio.h>
#include <string.h>
#define MAX_MACRO_NAME_LENGTH 31

typedef struct Macro {
  char *name;
  LinkedList *lines;
} Macro;

Macro *create_macro();
void add_macro_name(Macro *macro, char name[]);
void append_macro_line(Macro *macro, char *line);
void free_macro(Macro *macro);
void output_macro(Macro *macro, FILE *output);

#endif