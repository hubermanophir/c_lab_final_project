#include "../../header_files/global.h"
#include "../../header_files/preprocessor/Macro.h"
#include <string.h>

typedef enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
} LineType;

int does_contain_whitespace(char *test_str) {
  char *temp;
  temp = test_str;

  temp = strpbrk(temp, INVALID_NAME_CHARS);

  /*got to end of the line with no space in the string isselff*/
  if (!temp) {
    return 1;
  }
  SKIP_WHITESPACE(temp);

  return temp ? 1 : 0;
}

static int is_valid_macro_name(char *name, Hashtable *existing_macros) {
  if (get_hashtable(existing_macros, name)) {
    return 0;
  }
  if (get_opcode_from_string(name) != -1) {
    return 0;
  }
  if (get_directive_from_string(name) != -1) {
    return 0;
  }
  if (does_contain_whitespace(name)) {
    return 0;
  }

  return 1;
}

LineType get_line_type(char *line, Hashtable *existing_macros) {
  char *tok;
  int is_valid = 1;

  Macro *existing_macro = (Macro *)get_hashtable(existing_macros, line);
  if (existing_macro) {
    return MACRO_CALL;
  }

  tok = strstr(line, "endmacr");
  if (tok) {
    return MACRO_DECLARATION;
  }
  tok = strstr(line, "macr");
  if (tok) {
    line = tok;
    line += 4;
    SKIP_WHITESPACE(line);
    is_valid = is_valid_macro_name(line, existing_macros);
    if (is_valid) {
    }
  }
  return MACRO_DECLARATION;
}