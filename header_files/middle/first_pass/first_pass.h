#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "../../global.h"
#include <stdio.h>

void first_pass(FILE *am_file, int *is_valid_file,
                Translation_Unit *translation_unit);

void free_symbol(void *symbol);

#endif