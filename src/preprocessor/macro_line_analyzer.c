#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/global.h"
#include "../../header_files/preprocessor/Macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum MacroLineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE,
  INVALID
} MacroLineType;

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

MacroLineType handle_invalid_name(InvalidMacroType type, char *name) {
  switch (type) {
  case DUPLICATE_DECLARATION:
    printf("Error: Duplicate macro declaration: %s\n", name);
    return INVALID;

  case INVALID_NAME:
    printf("Error: Invalid macro name: %s\n", name);
    return INVALID;

  case OPT_NAME:
    printf("Error: Macro name is an opcode: %s\n", name);
    return INVALID;

  case DIRECTIVE_NAME:
    printf("Error: Macro name is a directive: %s\n", name);
    return INVALID;

  case EXISTING:
    printf("Error: Macro name already exists: %s\n", name);
    return INVALID;

  case LENGTH_ERROR:
    printf("Error: Macro name is too long: %s\n", name);
    return INVALID;

  default:
    return MACRO_DECLARATION;
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
  if (get_macro_hashtable(existing_macros, name)) {
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

int check_macro_isolated_line(char *line, char *name) {
  if (strncmp(line, name, strlen(name)) || line[strlen(name)] != '\0') {
    printf("Error: Macro call is not isolated\n");
    return 0;
  }
  return 1;
}

void print_names(char **names, int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("names[i] = %s, i:%d\n", names[i], i);
  }
}

char *get_macro_in_line(char *line, char **existing_names, int size) {
  int i;
  for (i = 0; i < size; i++) {
    if (strstr(line, existing_names[i])) {
      return existing_names[i];
    }
  }
  return NULL;
}

MacroLineType get_line_type(char *line, Hashtable *existing_macros,
                       Macro *current_macro) {
  char *tok, *is_macro_in_line;
  Macro *existing_macro;
  int size, i, is_valid;
  char **existing_names;

  /*clean line \n and trailing whitespace*/
  if (strlen(line) > 0) {
    line[strlen(line) - 1] = '\0';
    trim_trailing_whitespace(line);
    SKIP_WHITESPACE(line);
  }

  size = get_existing_macro_names(existing_macros, &existing_names);
  is_macro_in_line = get_macro_in_line(line, existing_names, size);
  free(existing_names);
  if (is_macro_in_line != NULL) {
    is_valid = check_macro_isolated_line(line, is_macro_in_line);
    if (!is_valid) {
      return INVALID;
    }
    existing_macro = (Macro *)get_macro_hashtable(existing_macros, line);
    if (existing_macro) {
      return MACRO_CALL;
    }
  }

  tok = strstr(line, "endmacr");
  if (tok) {
    i = strncmp(line, "endmacr", 7);
    if (!i) {
      line = tok;
      line += 7;
      SKIP_WHITESPACE(line);

      /*Nothing other then macro end*/
      if (*line == '\0') {
        return MACRO_END;
      } else {
        printf("Error: Invalid macro end\n");
        return INVALID;
      }
    }
  }
  tok = strstr(line, "macr");
  if (tok) {
    i = strncmp(line, "macr", 4);
    if (!i) {
      line = tok;
      line += 4;
      SKIP_WHITESPACE(line);
      return handle_invalid_name(is_valid_macro_name(line, existing_macros),
                                 line);
    }
  }

  return CODE_LINE;
}