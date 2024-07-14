#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_LINE_LENGTH 81

#include <ctype.h>

#define SKIP_WHITESPACE(ptr)                                                   \
  while (isspace(*(ptr))) {                                                    \
    (ptr)++;                                                                   \
  }

#define SPACE_CHARS " \t\n\v\f"

#define INVALID_NAME_CHARS ".,; \t\n\v\f"

typedef enum Opcode {
  MOV,
  CMP,
  ADD,
  SUB,
  LEA,
  CLR,
  NOT,
  INC,
  DEC,
  JMP,
  BNE,
  RED,
  PRN,
  JSR,
  RTS,
  STOP
} Opcode;

Opcode get_opcode_from_string(char *opcode);

typedef enum Directive { DATA, STRING, ENTRY, EXTERN } Directive;
Directive get_directive_from_string(char *directive);

void trim_trailing_whitespace(char *str);

#endif