#define MAX_LINE_LENGTH 81

#define SKIP_WHITE_SPACES(ptr)                                                 \
  while (*ptr == ' ' || *ptr == '\t')                                          \
  ptr++

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