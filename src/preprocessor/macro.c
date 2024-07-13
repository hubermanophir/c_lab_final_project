#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/data_structures/hashtable.h"
#include <stdio.h>
#include <stdlib.h>

void init_macro(Hashtable *macros, Macro *macro, char *name) {
  macro = (Macro *)malloc(sizeof(Macro));
  macro->name = name;
  macro->lines = (LinkedList *)malloc(sizeof(LinkedList));
  init_list(macro->lines);
  put_hashtable(macros, name, macro);
}

Macro *create_or_find_macro(Hashtable *macros, char *name) {
  Macro *macro = get_hashtable(macros, name);

  if (!macro) {
    init_macro(macros, macro, name);
  }

  return macro;
}

void append_macro_line(Macro *macro, char *line) {
  add_to_list(macro->lines, line);
}

void free_macro(Macro *macro) {
  free_list(macro->lines);
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