#ifndef GLOBAL_H
#define GLOBAL_H

#define MAX_LINE_LENGTH 81

#include <ctype.h>

#define SKIP_WHITESPACE(ptr)                                                   \
  while (isspace(*(ptr))) {                                                    \
    (ptr)++;                                                                   \
  }

#define SPACE_CHARS " \t\n\v\f"

#define INVALID_NAME_CHARS ",; \t\n\v\f"

#define MAX_DATA_SIZE 100

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

/**
 * @brief Get the opcode from string
 *
 * @param opcode
 * @return Opcode
 */
Opcode get_opcode_from_string(char *opcode);

typedef enum Directive { DATA, STRING, ENTRY, EXTERN } Directive;

/**
 * @brief Get the directive from string object
 *
 * @param directive
 * @return Directive
 */
Directive get_directive_from_string(char *directive);

/**
 * @brief trim the ending whitespace from a string
 *
 * @param str
 */
void trim_trailing_whitespace(char *str);

/**
 * @brief makes copy of str
 * 
 * @param str 
 * @return copy of str 
 */
char *make_char_copy(char *str);

typedef struct Line_obj {
  char error[150];
  char label[100];
  enum { EMPTY, COMMENT, DIRECTIVE, INSTRUCTION } LineType;
  union {
    struct {
      Directive directive_option;
      union {
        char *label;
        char *str;
        struct {
          int numbers[MAX_DATA_SIZE];
          int length;
        } data;
      } directive_operand;
    } directive;
    struct {
      Opcode opcode_option;
      struct {
        int register_index;
        char *label;
        int immediate;
      } operands[2];
      enum { IMMEDIATE, DIRECT, INDIRECT, REGISTER, NONE } addressing[2];
      int length;
    } instruction;
  } test;
} Line_obj;

#endif