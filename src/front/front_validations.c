#include "../../header_files/front/directive_line_validations.h"
#include "../../header_files/front/instruction_line_validations.h"

#include "../../header_files/front/validation_types.h"
#include "../../header_files/global.h"

#include <string.h>
/**
 * @brief This function gets the tokens and removes the first one
 *
 * @param tokens_obj
 */
void remove_first_token(Tokens_Obj *tokens_obj) {
  int i;
  for (i = 1; i < tokens_obj->size; i++) {
    tokens_obj->tokens[i - 1] = tokens_obj->tokens[i];
  }
  tokens_obj->size--;
}

/**
 * @brief Gets the tokens and if the first token is a label, updates the label
 * and removes the token
 *
 * @param tokens_obj
 * @param line_obj
 */
void update_label_declaration(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
  char *first_token = tokens_obj->tokens[0];
  if (strlen(first_token) > 1 && first_token[strlen(first_token) - 1] == ':') {
    first_token[strlen(first_token) - 1] = '\0';
    strcpy(line_obj->label, first_token);
    /*skip token to next token*/
    remove_first_token(tokens_obj);
    return;
  }
  strcpy(line_obj->label, "");
}

/**
 * @brief Should validate the instruction line
 We know there is opcode as part of the tokens
 *
 * @param tokens_obj
 * @param line_obj
 */
void validate_instruction_line(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
  Opcode opcode;
  Operands operands;
  update_label_declaration(tokens_obj, line_obj);
  /*the opcode should be first*/
  opcode = get_opcode_from_string(tokens_obj->tokens[0]);
  if (opcode == -1) {
    strcpy(line_obj->error, "Invalid line opcode not in correct position");
    line_obj->LineType = ERROR;
    return;
  }
  line_obj->line_type.instruction.opcode_option = opcode;
  remove_first_token(tokens_obj);
  operands = get_operands(tokens_obj, line_obj);
  if (strcmp(line_obj->error, "") != 0) {
    return;
  }
  validate_operands(operands, line_obj, opcode);
  if (strcmp(line_obj->error, "") != 0) {
    return;
  }
  update_operands(line_obj, operands);
}

/**
 * @brief This function validates the directive line
 *
 * @param tokens_obj
 * @param line_obj
 * @param line
 */
void validate_directive_line(Tokens_Obj *tokens_obj, Line_obj *line_obj,
                             char *line) {
  Directive directive;
  update_label_declaration(tokens_obj, line_obj);
  directive = get_directive_from_string(tokens_obj->tokens[0]);
  if (directive == -1) {
    strcpy(line_obj->error, "Invalid directive");
    line_obj->LineType = ERROR;
    return;
  }
  line_obj->line_type.directive.directive_option = directive;
  remove_first_token(tokens_obj);
  validate_and_update_directive(line_obj, line, directive, tokens_obj);
}