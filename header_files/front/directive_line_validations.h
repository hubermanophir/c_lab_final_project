#ifndef DIRECTIVE_LINE_VALIDATIONS_H
#define DIRECTIVE_LINE_VALIDATIONS_H

#include "../front/helper_functions.h"
#include "../global.h"

/**
 * @brief Updating the line object with the directive data
 * 
 * @param line_obj 
 * @param line 
 * @param directive 
 * @param tokens_obj 
 */
void validate_and_update_directive(Line_obj *line_obj, char *line,
                                   Directive directive, Tokens_Obj *tokens_obj);

#endif