#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/global.h"
#include "../../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <string.h>

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
  tok = strstr(line, "macr");
  if (tok) {
    SKIP_WHITESPACE(line);
    is_valid = is_valid_macro_name(line, existing_macros);
    printf("is_valid: %d\n", is_valid);
  }
  return MACRO_DECLARATION;
}