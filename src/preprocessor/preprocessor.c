#include "../../header_files/global.h"
#include "../../header_files/preprocessor/helper.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/macro_line_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *preprocessor(char *file_name) {
  char line[MAX_LINE_LENGTH];
  char *tok;
  FILE *as_file, *an_file;
  Macro *current_macro = NULL;
  LineType line_type;

  Hashtable *macros = create_hashtable(100);

  char *as_file_name = get_file_name(file_name, ".as");
  char *an_file_name = get_file_name(file_name, ".an");
  as_file = fopen(as_file_name, "r");
  an_file = fopen(an_file_name, "w");

  if (!as_file || !an_file) {
    free(as_file_name);
    free(an_file_name);
    free_macro_hashtable(macros);
    return NULL;
  }

  while (fgets(line, MAX_LINE_LENGTH, as_file)) {

    line_type = get_line_type(line, macros, current_macro);

    switch (line_type) {
    case MACRO_DECLARATION: {
      tok = strstr(line, "macr");
      tok += 4;
      SKIP_WHITESPACE(tok);

      current_macro = create_macro();
      add_macro_name(current_macro, tok);
      put_hashtable(macros, tok, current_macro);
      break;
    }
    case MACRO_END: {
      current_macro = NULL;
      break;
    }
    case MACRO_CALL: {
      tok = line;
      SKIP_WHITESPACE(tok);
      trim_trailing_whitespace(tok);
      current_macro = (Macro *)get_macro_hashtable(macros, tok);
      output_macro(current_macro, an_file);
      current_macro = NULL;
      break;
    }
    case CODE_LINE: {
      if (current_macro) {
        append_macro_line(current_macro, line);
      } else {
        fputs(line, an_file);
        fputs("\n", an_file);
      }

      break;
    }
    }
  }
  fclose(an_file);
  fclose(as_file);
  free_macro_hashtable(macros);
  free(as_file_name);

  return an_file_name;
}
