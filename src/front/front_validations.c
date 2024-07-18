#include "../../header_files/global.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Operand_Type { REG, LABEL, IM, INV } Operand_Type;
/*
int convert_number_str_to_int(char *str) {
  char *endptr;
  int num = strtol(str, &endptr, 10);
  if (*endptr != '\0') {
    return 0;
  }
  return num;
}

int is_number(char *str) {
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return MIN_VALUE;
    }
  }
  return convert_number_str_to_int(str);
}
Operand_Type get_operand_type(char *operand) {
  char *tok;
  if (operand[0] == 'r' && isdigit(operand[1]) && strlen(operand) == 2) {
    return REG;
  } else if (is_number(operand) != MIN_VALUE) {
    return IM;
  } else {
    tok = strpbrk(operand, INVALID_LABEL_CHARS);
    if (tok == NULL) {
      return LABEL;
    }
  }
  return INV;
}

AddressingMode get_addressing_mode(char *operand, Operand_Type operand_type) {
  if (operand[0] == '#' && operand_type == IM) {
    return IMMEDIATE;
  } else if (operand[0] == '*' && operand_type == REG) {
    return INDIRECT_ACCUMULATE;
  } else if (operand[0] == 'r' && operand_type == REG) {
    return DIRECT_ACCUMULATE;
  } else if (operand_type == LABEL) {
    return DIRECT;
  }
  return NONE;
}

*/
/*
Label can be in the beginning like so
LABEL:
or
mov LABEL, 5


*/
char *get_label(Tokens_Obj tokens_obj) { return ""; }

/*

can Have 0,1,2 operands

can be written like so:
1.              size = 0
2. op1          size = 1
3. ,            size = 1
3. op1 ,        size = 2
4. , op2        size = 2
4. op1 op2      size = 2
5. op1 , op2    size = 3


*/

void remove_first_token(Tokens_Obj *tokens_obj) {
  int i;
  for (i = 1; i < tokens_obj->size; i++) {
    tokens_obj->tokens[i - 1] = tokens_obj->tokens[i];
  }
  tokens_obj->size--;
}

typedef struct Operands {
  char *operand1;
  char *operand2;
  int amount;
} Operands;

int is_comma_str(char *str) { return *str == ','; }

Operands get_operands(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
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

static void update_label_declaration(Tokens_Obj *tokens_obj,
                                     Line_obj *line_obj) {
  int i;
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
}

void validate_directive_line(Tokens_Obj *tokens_obj, Line_obj *line_obj) {
  update_label_declaration(tokens_obj, line_obj);
}

int is_comment_line(char *line) { return *line == ';'; }

int is_empty_line(char *line) { return *line == '\0'; }
