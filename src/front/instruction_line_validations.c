#include "../../header_files/front/helper_functions.h"
#include "../../header_files/front/validation_types.h"
#include "../../header_files/global.h"
#include <stdio.h>
#include <string.h>

AddressingMode get_addressing_mode(char *operand) {
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

int valid_operand_groups(Valid_groups first_argument_group,
                         Valid_groups second_argument_group,
                         Operands operands) {
  return is_in_group(first_argument_group,
                     get_addressing_mode(operands.operand1)) &&
         is_in_group(second_argument_group,
                     get_addressing_mode(operands.operand2));
}

void validate_operands(Operands operands, Line_obj *line_obj, Opcode opcode) {
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