#include "../../header_files/global.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/helper.h"
#include "../../header_files/preprocessor/macro_line_analizer.h"

#include <stdio.h>
#include <stdlib.h>

void preprocessor(char *file_name) {
  char line[MAX_LINE_LENGTH];
  Macro *current_macro = NULL;
  Hashtable *macros = create_hashtable(100);
  char *as_file_name = get_file_name(file_name, ".an");
  char *an_file_name = get_file_name(file_name, ".an");

  printf("as file:%s \n", as_file_name);

  free(as_file_name);
  free(an_file_name);
}