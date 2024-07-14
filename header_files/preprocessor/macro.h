#ifndef MACRO_H
#define MACRO_H

#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/data_structures/linked_list.h"
#include <stdio.h>
#include <string.h>

typedef struct Macro {
  char *name;
  LinkedList *lines;
} Macro;

void init_macro(Hashtable *macros, Macro *macro, char *name);
Macro *create_or_find_macro(Hashtable *macros, char *name);
void append_macro_line(Macro *macro, char *line);
void free_macro(Macro *macro);
void output_macro(Macro *macro, FILE *output);

#endif