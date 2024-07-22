#ifndef MIDDLE_H
#define MIDDLE_H
#include "../data_structures/linked_list.h"
#include "../global.h"
#include "./first_pass/first_pass.h"
#include <stdio.h>

void middle(FILE *am_file, int *is_valid_file,
            Translation_Unit *translation_unit, char *file_name);

#endif