#include "../../header_files/middle/first_pass/first_pass.h"
#include "../../header_files/middle/second_pass/second_pass.h"

#include <stdio.h>

void middle(FILE *am_file, int *is_valid_file,
            Translation_Unit *translation_unit) {
  first_pass(am_file, is_valid_file, translation_unit);
  second_pass();
}