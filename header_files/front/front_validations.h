#ifndef FRONT_VALIDATIONS_H
#define FRONT_VALIDATIONS_H
#include "../global.h"

/**
 * @brief Checks if instruction line is valid if not update error message
 * Opcode detected, should check the syntax
 for 0, 1, 2 operands
 * @param tokens_obj
 * @return int 1 if valid 0 if not
 */
void validate_instruction_line(Tokens_Obj tokens_obj, Line_obj line_obj);

/**
 * @brief Checks if directive line is valid if not update error message
 *
 * @param tokens_obj
 * @return int 1 if valid 0 if not
 */
void validate_directive_line(Tokens_Obj tokens_obj, Line_obj line_obj);

/**
 * @brief Checks if comment line
 *
 * @param line
 * @return int
 */
int is_comment_line(char *line);


/**
 * @brief Checks if empty line
 * 
 * @param line 
 * @return int 
 */
int is_empty_line(char *line);
#endif