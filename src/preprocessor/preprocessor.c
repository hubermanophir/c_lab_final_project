#include "../../header_files/global.h"
#include "../../header_files/preprocessor/helper.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/macro_line_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *preprocessor(char *file_name) {
  char line[MAX_LINE_LENGTH];
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
      printf("MACRO_DECLARATION %s\n", line);
      break;
    }
    case MACRO_END: {
      printf("MACRO_END %s\n", line);

      break;
    }
    case MACRO_CALL: {
      printf("MACRO_CALL %s\n", line);

      break;
    }
    case CODE_LINE: {
      printf("CODE_LINE %s\n", line);

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
