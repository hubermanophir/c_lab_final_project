#include "../../header_files/global.h"
#include "../../header_files/preprocessor/helper.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/macro_line_analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *preprocessor(char *file_name) {
  char line[MAX_LINE_LENGTH], line_copy[MAX_LINE_LENGTH];
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
    strcpy(line_copy, line);
    line_type = get_line_type(line_copy, macros);
  }

  fclose(an_file);
  fclose(as_file);
  free_hashtable(macros);
  free(as_file_name);
  free(an_file_name);
  return an_file_name;
}