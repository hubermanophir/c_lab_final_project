#include "../../header_files/data_structures/linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Macro {
  char *name;
  LinkedList *lines;
} Macro;

Macro *create_macro() {
  Macro *macro = (Macro *)malloc(sizeof(Macro));
  macro->name = NULL;
  macro->lines = init_list();
  return macro;
}

void add_macro_name(Macro *macro, char name[]) {
  macro->name = (char *)malloc(strlen(name) + 1);
  if (macro->name != NULL) {
    strcpy(macro->name, name);
  }
}

void append_macro_line(Macro *macro, char *line) {
  char *line_copy = (char *)malloc(strlen(line) + 1);
  if (line_copy != NULL) {
    strcpy(line_copy, line);
    add_to_list(macro->lines, line_copy);
  } else {
    exit(1);
  }
}
void free_macro(Macro *macro) {
  free_list((macro->lines));
  free(macro->name);
  free(macro);
}

void output_macro(Macro *macro, FILE *output) {
  Node *current = macro->lines->head;
  while (current) {
    fputs((char *)current->data, output);
    current = current->next;
  }
}