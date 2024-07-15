#include "../../header_files/global.h"
#include "../../header_files/preprocessor/Macro.h"
#include "../../header_files/data_structures/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
} LineType;

typedef enum InvalidMacroType {
  DUPLICATE_DECLARATION,
  INVALID_NAME,
  OPT_NAME,
  DIRECTIVE_NAME,
  EXISTING,
  SYMBOL,
  LENGTH_ERROR,
  VALID
} InvalidMacroType;

void handle_invalid_name(InvalidMacroType type, char *name) {
  switch (type) {
  case DUPLICATE_DECLARATION:
    printf("Error: Duplicate macro declaration: %s\n", name);
    exit(1);
    break;
  case INVALID_NAME:
    printf("Error: Invalid macro name: %s\n", name);
    exit(1);
    break;
  case OPT_NAME:
    printf("Error: Macro name is an opcode: %s\n", name);
    exit(1);
    break;
  case DIRECTIVE_NAME:
    printf("Error: Macro name is a directive: %s\n", name);
    exit(1);
    break;
  case EXISTING:
    printf("Error: Macro name already exists: %s\n", name);
    exit(1);
    break;
  case LENGTH_ERROR:
    printf("Error: Macro name is too long: %s\n", name);
    exit(1);
    break;
  default:
    break;
  }
}

static int does_contain_invalid_chars(char *test_str) {
  char *temp;
  temp = test_str;

  temp = strpbrk(temp, INVALID_NAME_CHARS);

  /*got to end of the line with no space in the string itself*/

  if (!temp) {
    return 0;
  }

  SKIP_WHITESPACE(temp);
  /*check if there is a second word which is invalid*/
  return temp ? 1 : 0;
}

static InvalidMacroType is_valid_macro_name(char *name,
                                            Hashtable *existing_macros) {
  if (get_hashtable(existing_macros, name)) {
    return EXISTING;
  }
  if (get_opcode_from_string(name) != -1) {
    return OPT_NAME;
  }
  if (get_directive_from_string(name) != -1) {
    return DIRECTIVE_NAME;
  }
  if (strlen(name) > 30) {
    return LENGTH_ERROR;
  }

  if (does_contain_invalid_chars(name)) {
    return INVALID_NAME;
  }

  return VALID;
}

void check_macro_isolated_line(char *line, char *name) {
  if (strncmp(line, name, strlen(name)) || line[strlen(name)] != '\0') {
    printf("Error: Macro name is not isolated\n");
    exit(1);
  }
}

LineType get_line_type(char *line, Hashtable *existing_macros,
                       Macro *current_macro) {
  char *tok;
  Macro *existing_macro;

  /*clean line \n and trailing whitespace*/
  if (strlen(line) > 0) {
    line[strlen(line) - 1] = '\0';
    trim_trailing_whitespace(line);
    SKIP_WHITESPACE(line);
  }

  existing_macro = (Macro *)get_hashtable(existing_macros, line);
  /*implement!!!!*/
  if (existing_macro) {
    return MACRO_CALL;
  }

  tok = strstr(line, "endmacr");
  if (tok) {
    line = tok;
    line += 7;
    SKIP_WHITESPACE(line);

    /*Nothing other then macro end*/
    if (*line == '\0') {
      return MACRO_END;
    } else {
      printf("Error: Invalid macro end\n");
      exit(1);
    }
  }
  tok = strstr(line, "macr");
  if (tok) {
    line = tok;
    line += 4;
    SKIP_WHITESPACE(line);
    handle_invalid_name(is_valid_macro_name(line, existing_macros), line);
    return MACRO_DECLARATION;
  }

  return CODE_LINE;
}