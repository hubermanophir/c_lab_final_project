#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "../../global.h"
#include <stdio.h>

void second_pass(FILE *am_file, int *is_valid_file,
                 Translation_Unit *translation_unit, char *file_name);
#endif