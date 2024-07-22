#ifndef GLOBAL_H
#define GLOBAL_H

#include "data_structures/hashtable.h"
#include "data_structures/linked_list.h"
#define MAX_LINE_LENGTH 81

#include <ctype.h>

#define SKIP_WHITESPACE(ptr)                                                   \
  while (isspace(*(ptr))) {                                                    \
    (ptr)++;                                                                   \
  }

#define SPACE_CHARS " \t\v\f"

#define TOKENIZE_CHARS ",\t\v\f "

#define INVALID_NAME_CHARS ",; \t\n\v\f"

#define INVALID_LABEL_CHARS ",;#$%^!@&*()+=- \t\n\v\f"

#define MAX_DATA_SIZE 100

#define MAX_LABEL_LENGTH 31

#define MIN_VALUE -32768

#define MAX_VALUE 32767

#define MAX_MEMORY_SIZE 4096

#define START_ADDRESS 100

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

typedef enum AddressingMode {
  IMMEDIATE = 1,           /*#3*/
  DIRECT = 2,              /*LABEL*/
  INDIRECT_ACCUMULATE = 4, /* *r2 */
  DIRECT_ACCUMULATE = 8,   /*r2*/
  NONE = 0
} AddressingMode;

typedef struct Line_obj {
  char error[MAX_DATA_SIZE];
  char label[MAX_LABEL_LENGTH];
  int line_number;
  enum { DIRECTIVE, INSTRUCTION, ERROR } LineType;
  union {
    struct {
      Directive directive_option;
      union {
        char label[MAX_LABEL_LENGTH];
        char string[MAX_LINE_LENGTH];
        struct {
          int numbers[MAX_DATA_SIZE];
          int length;
        } data;
      } directive_operand;
    } directive;
    struct {
      Opcode opcode_option;
      union {
        int register_index;
        char label[MAX_LABEL_LENGTH];
        int immediate;
      } operands[2];
      AddressingMode addressing[2];
      int length;
    } instruction;
  } line_type;
} Line_obj;

typedef struct Tokens_Obj {
  char *tokens[MAX_LABEL_LENGTH];
  int size;
} Tokens_Obj;

typedef struct Symbol {
  char *name;
  int address;
  enum { external, entry, code, data, ent_data, ent_code } symbol_type;
} Symbol;

typedef struct Extern {
  char *name;
  int address[MAX_MEMORY_SIZE];
  int addresses_count;
} Extern;

typedef struct Ent {
  char *name;
  int address;
} Ent;

typedef struct Translation_Unit {
  int ic;
  int code_image[MAX_MEMORY_SIZE];
  int dc;
  int data_image[MAX_MEMORY_SIZE];
  Hashtable *symbols_table;
  int symbols_count;
  Hashtable *externals;
  int externals_count;
  Hashtable *entries;
  int entries_count;
} Translation_Unit;

int is_register(AddressingMode addressing);

typedef enum ARE { A = 4, R = 2, E = 1 } ARE;

#endif