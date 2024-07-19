#ifndef INSTRUCTION_LINE_VALIDATIONS_H
#define INSTRUCTION_LINE_VALIDATIONS_H
#include "../../header_files/front/helper_functions.h"
#include "../../header_files/front/validation_types.h"
#include "../../header_files/global.h"

/**
 * @brief This function check for the operand which addressing mode is it
 *
 * @param operand
 * @return AddressingMode
 */
AddressingMode get_addressing_mode(char *operand);

/**
 * @brief Get the operands and checks for correct comma placement
 *
 * @param tokens_obj
 * @param line_obj
 * @return Operands
 */
Operands get_operands(Tokens_Obj *tokens_obj, Line_obj *line_obj);

/**
 * @brief Checks for given group if the addressing mode is in the group
 *
 * @param group
 * @param addressing
 * @return int
 */
int is_in_group(Valid_groups group, AddressingMode addressing);

/**
 * @brief This function matches between the given operands and the given groups
 *
 * @param first_argument_group
 * @param second_argument_group
 * @param operands
 * @return int 1 if valid, 0 if not

 */
int valid_operand_groups(Valid_groups first_argument_group,
                         Valid_groups second_argument_group, Operands operands);

/**
* @brief This function checks for the given operands and opcode if the amount of
arguments is correct and the source and destination addressing modes are valid
*
* @param operands
* @param line_obj
* @param opcode
*/
void validate_operands(Operands operands, Line_obj *line_obj, Opcode opcode);

#endif