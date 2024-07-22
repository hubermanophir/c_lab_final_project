#include "../header_files/global.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get the opcode from string
 *
 * @param opcode
 * @return Opcode
 */
Opcode get_opcode_from_string(char *opcode) {

  if (strcmp(opcode, "mov") == 0) {
    return MOV;
  } else if (strcmp(opcode, "cmp") == 0) {
    return CMP;
  } else if (strcmp(opcode, "add") == 0) {
    return ADD;
  } else if (strcmp(opcode, "sub") == 0) {
    return SUB;
  } else if (strcmp(opcode, "lea") == 0) {
    return LEA;
  } else if (strcmp(opcode, "clr") == 0) {
    return CLR;
  } else if (strcmp(opcode, "not") == 0) {
    return NOT;
  } else if (strcmp(opcode, "inc") == 0) {
    return INC;
  } else if (strcmp(opcode, "dec") == 0) {
    return DEC;
  } else if (strcmp(opcode, "jmp") == 0) {
    return JMP;
  } else if (strcmp(opcode, "bne") == 0) {
    return BNE;
  } else if (strcmp(opcode, "red") == 0) {
    return RED;
  } else if (strcmp(opcode, "prn") == 0) {
    return PRN;
  } else if (strcmp(opcode, "jsr") == 0) {
    return JSR;
  } else if (strcmp(opcode, "rts") == 0) {
    return RTS;
  } else if (strcmp(opcode, "stop") == 0) {
    return STOP;
  }
  return -1;
}

Directive get_directive_from_string(char *directive) {
  if (strcmp(directive, ".data") == 0) {
    return DATA;
  } else if (strcmp(directive, ".string") == 0) {
    return STRING;
  } else if (strcmp(directive, ".entry") == 0) {
    return ENTRY;
  } else if (strcmp(directive, ".extern") == 0) {
    return EXTERN;
  }
  return -1;
}

void trim_trailing_whitespace(char *str) {
  int len = strlen(str);
  while (len > 0 && isspace(str[len - 1])) {
    str[len - 1] = '\0';
    len--;
  }
}

char *make_char_copy(char *str) {
  char *copy = (char *)malloc(strlen(str) + 1);
  strcpy(copy, str);
  return copy;
}

int is_register(AddressingMode addressing) {
  return addressing == DIRECT_ACCUMULATE || addressing == INDIRECT_ACCUMULATE;
}