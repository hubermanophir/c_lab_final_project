#include "../../header_files/global.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operands {
  char *operand1;
  char *operand2;
  int amount;
} Operands;

/*
This means the possible addressing modes
Ex: mov source can be 0,1,2,3
    des can be 1,2,3
*/
typedef enum Valid_groups {
  ONE_GROUP, /*1*/
  TWO_GROUP, /*1,2*/
  THREE_GROUP,/*1,2,3*/
  FOUR_GROUP,/*0,1,2,3*/
  NONE_GROUP  /*NONE*/
} Valid_groups;

static int convert_number_str_to_int(char *str) {
  char *endptr;
  int num = strtol(str, &endptr, 10);
  if (*endptr != '\0') {
    return 0;
  }
  return num;
}

/**
 * @brief Checks if a string is a number and if it is it converts it
 * 
 * @param str 
 * @return int 
 */
static int is_number(char *str) {
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return MIN_VALUE;
    }
  }
  return convert_number_str_to_int(str);
}

/**
 * @brief Checks if a register number is between 0-7
 * 
 * @param str 
 * @return int 
 */
static int is_valid_reg_num(char *str) {
  int num = is_number(str);
  if (num == MIN_VALUE) {
    return 0;
  }
  if (num < 0 || num > 7) {
    return 0;
  }
  return 1;
}

/**
 * @brief This function gets the tokens and removes the first one
 * 
 * @param tokens_obj 
 */
static void remove_first_token(Tokens_Obj *tokens_obj) {
  int i;
  for (i = 1; i < tokens_obj->size; i++) {
    tokens_obj->tokens[i - 1] = tokens_obj->tokens[i];
  }
  tokens_obj->size--;
}

/**
 * @brief simple check if a string is a comma
 * 
 * @param str 
 * @return int 
 */
int is_comma_str(char *str) { return *str == ','; }

/**
 * @brief This function check for the operand which addressing mode is it
 * 
 * @param operand 
 * @return AddressingMode 
 */
static AddressingMode get_addressing_mode(char *operand) {
  if (operand == NULL) {
    return NONE;
  } else if (operand[0] == '#' && is_number(operand + 1) != MIN_VALUE) {
    return IMMEDIATE;
  } else if (operand[0] == '*' && is_valid_reg_num(operand + 1)) {
    return INDIRECT_ACCUMULATE;
  } else if (operand[0] == 'r' && is_valid_reg_num(operand + 1)) {
    return DIRECT_ACCUMULATE;
  } else if (strpbrk(operand, INVALID_LABEL_CHARS) == NULL) {
    return DIRECT;
  }
  return NONE;
}

/**
 * @brief Get the operands and checks for correct comma placement
 * 
 * @param tokens_obj 
 * @param line_obj 
 * @return Operands 
 */
static Operands get_operands(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
  Operands operands;
  operands.operand1 = NULL;
  operands.operand2 = NULL;
  operands.amount = 0;
  if ((tokens_obj->size > 0) && is_comma_str(tokens_obj->tokens[0])) {
    strcpy(line_obj->error, "Invalid line, comma after opcode");
    return operands;
  }
  if ((tokens_obj->size > 1) &&
      is_comma_str(tokens_obj->tokens[tokens_obj->size - 1])) {
    strcpy(line_obj->error, "Invalid line, comma at the end");
    return operands;
  }
  switch (tokens_obj->size) {
  case 0:
    return operands;
  case 1:
    operands.operand1 = tokens_obj->tokens[0];
    operands.amount = 1;
    return operands;
  case 2:
    strcpy(line_obj->error, "Invalid line, missing comma between operands");
    return operands;
  case 3:
    if (is_comma_str(tokens_obj->tokens[1])) {
      operands.operand1 = tokens_obj->tokens[0];
      operands.operand2 = tokens_obj->tokens[2];
      operands.amount = 2;
      return operands;
    } else {
      strcpy(line_obj->error,
             "Invalid line, should get 2 operands separated by comma");
      return operands;
    }
  default:
    strcpy(line_obj->error, "Invalid line, invalid number of operands");
    return operands;
  }
}

/**
 * @brief Gets the tokens and if the first token is a label, updates the label and removes the token
 * 
 * @param tokens_obj 
 * @param line_obj 
 */
static void update_label_declaration(Tokens_Obj *tokens_obj,
                                     Line_obj *line_obj) {
  char *first_token = tokens_obj->tokens[0];
  if (strlen(first_token) > 2 && first_token[strlen(first_token) - 1] == ':') {
    first_token[strlen(first_token) - 1] = '\0';
    strcpy(line_obj->label, first_token);
    /*skip token to next token*/
    remove_first_token(tokens_obj);
    return;
  }
  strcpy(line_obj->label, "");
}

/**
 * @brief Checks for given group if the addressing mode is in the group
 * 
 * @param group 
 * @param addressing 
 * @return int 
 */
int is_in_group(Valid_groups group, AddressingMode addressing) {
  switch (group) {
  case ONE_GROUP:
    return addressing == DIRECT;
  case TWO_GROUP:
    return addressing == DIRECT || addressing == INDIRECT_ACCUMULATE;
  case THREE_GROUP:
    return addressing == DIRECT || addressing == INDIRECT_ACCUMULATE ||
           addressing == DIRECT_ACCUMULATE;
  case FOUR_GROUP:
    return addressing == IMMEDIATE || addressing == DIRECT ||
           addressing == INDIRECT_ACCUMULATE || addressing == DIRECT_ACCUMULATE;
  case NONE_GROUP:
    return addressing == NONE;
  default:
    return 0;
  }
}

/**
 * @brief This function matches between the given operands and the given groups
 * 
 * @param first_argument_group 
 * @param second_argument_group 
 * @param operands 
 * @return int 1 if valid, 0 if not
 
 */
int valid_operand_groups(Valid_groups first_argument_group,
                         Valid_groups second_argument_group,
                         Operands operands) {
  return is_in_group(first_argument_group,
                     get_addressing_mode(operands.operand1)) &&
         is_in_group(second_argument_group,
                     get_addressing_mode(operands.operand2));
}

/**
 * @brief This function checks for the given operands and opcode if the amount of
 arguments is correct and the source and destination addressing modes are valid
 * 
 * @param operands 
 * @param line_obj 
 * @param opcode 
 */
static void validate_operands(Operands operands, Line_obj *line_obj,
                              Opcode opcode) {
  switch (opcode) {
  case MOV:
  case ADD:
  case SUB: {
    if (!valid_operand_groups(FOUR_GROUP, THREE_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case CMP: {
    if (!valid_operand_groups(FOUR_GROUP, FOUR_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case LEA: {
    if (!valid_operand_groups(ONE_GROUP, THREE_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case CLR:
  case NOT:
  case INC:
  case DEC:
  case RED: {
    if (operands.amount > 1) {
      strcpy(line_obj->error, "Invalid line, too many operands");
      break;
    }

    if (!valid_operand_groups(THREE_GROUP, NONE_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case JMP:
  case BNE:
  case JSR: {
    if (operands.amount > 1) {
      strcpy(line_obj->error, "Invalid line, too many operands");
      break;
    }
    if (!valid_operand_groups(TWO_GROUP, NONE_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case PRN: {
    if (operands.amount > 1) {
      strcpy(line_obj->error, "Invalid line, too many operands");
      break;
    }
    if (!valid_operand_groups(FOUR_GROUP, NONE_GROUP, operands)) {
      strcpy(line_obj->error, "Invalid line, incorrect operand types");
    }
    break;
  }
  case RTS:
  case STOP: {
    if (operands.amount != 0) {
      strcpy(line_obj->error, "Invalid line, too many operands");
      return;
    }
  }
  }
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
    return;
  }
  line_obj->line_type.instruction.opcode_option = opcode;
  remove_first_token(tokens_obj);
  operands = get_operands(tokens_obj, line_obj);
  if (strcmp(line_obj->error, "") != 0) {
    return;
  }
  validate_operands(operands, line_obj, opcode);
}

void validate_directive_line(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
  update_label_declaration(tokens_obj, line_obj);
}

int is_comment_line(char *line) { return *line == ';'; }

int is_empty_line(char *line) { return *line == '\0'; }
