#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include "../../data_structures/linked_list.h"
#include "../../global.h"

typedef struct Symbol {
  char name[MAX_LABEL_LENGTH];
  int address;
  enum { external, entry, code, data } symbol_type;
} Symbol;

void first_pass(LinkedList *lines, int *is_valid_file);

#endif