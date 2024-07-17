#include "../../header_files/global.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef enum Operand_Type { REG, LABEL, IM, INV } Operand_Type;

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
1.
2. op1
3. op1,op2
4. op1, op2
5. op1 ,op2
6. op1 , op2

*/
void validate_instruction_line(Tokens_Obj tokens_obj, Line_obj line_obj) {}

void validate_directive_line(Tokens_Obj tokens_obj, Line_obj line_obj) {}

int is_comment_line(char *line) { return *line == ';'; }

int is_empty_line(char *line) { return *line == '\0'; }
