#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "../../global.h"
#include <stdio.h>

/**
 * @brief This function builds the symbols table in the translation unit
 and adds the data_image
 *
 * @param am_file
 * @param is_valid_file
 * @param translation_unit
 */
void first_pass(FILE *am_file, int *is_valid_file,
                Translation_Unit *translation_unit);

/**
 * @brief This frees the symbol struct memory
 *
 * @param symbol
 */
void free_symbol(void *symbol);

#endif