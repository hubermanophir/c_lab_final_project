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
  char *name;
  FILE *as_file, *an_file;
  Macro *current_macro = NULL;
  LineType line_type;

  Hashtable *macros = create_hashtable(100);
  char *as_file_name = get_file_name(file_name, ".as");
  char *an_file_name = get_file_name(file_name, ".an");
  printf("as file:%s \n", as_file_name);
  as_file = fopen(as_file_name, "r");
  an_file = fopen(an_file_name, "w");
  if (!as_file || !an_file) {
    return NULL;
  }

  while (fgets(line, MAX_LINE_LENGTH, as_file)) {
    line_type = get_line_type(line, macros, current_macro);
    switch (line_type) {
    case MACRO_DECLARATION: {
      tok = strstr(line, "macr");
      tok += 4;
      SKIP_WHITESPACE(tok);
      trim_trailing_whitespace(tok);
      name = tok;
      printf("name:%s\n", name);
      current_macro = create_macro();
      add_macro_name(current_macro, name);
      put_hashtable(macros, name, current_macro);
      break;
    }
    case MACRO_END: {
      current_macro = NULL;
      break;
    }
    case MACRO_CALL: {
      output_macro((Macro *)get_hashtable(macros, current_macro->name),
                   an_file);
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
  free(an_file_name);
  return an_file_name;
}

/*

 Macro *macro = create_macro();
  Macro *macro2 = create_macro();
  FILE *an_file;
  Hashtable *table = create_hashtable(100);

  preprocessor(argv[1]);
  an_file = fopen("output.an", "w");
  add_macro_name(macro, "MACRO");
  add_macro_name(macro2, "MACRO2");

  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");
  append_macro_line(macro, "LINE 1\n");

  put_hashtable(table, "MACRO", macro);
  put_hashtable(table, "MACRO2", macro2);
  append_macro_line(macro2, "M2LINE 1\n");
  append_macro_line(macro2, "M2LINE 1\n");
  append_macro_line(macro2, "M2LINE 1\n");

  output_macro((Macro *)get_hashtable(table, "MACRO"), an_file);
  output_macro((Macro *)get_hashtable(table, "MACRO2"), an_file);

  fclose(an_file);
  free_macro_hashtable(table);
*/