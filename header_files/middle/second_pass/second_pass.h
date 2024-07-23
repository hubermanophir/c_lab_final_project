#ifndef SECOND_PASS_H
#define SECOND_PASS_H

#include "../../global.h"
#include <stdio.h>

/**
 * @brief This function adds the code_image and verifies the symbols as args
 * 
 * @param am_file 
 * @param is_valid_file 
 * @param translation_unit 
 */
void second_pass(FILE *am_file, int *is_valid_file,
                 Translation_Unit *translation_unit);
#endif