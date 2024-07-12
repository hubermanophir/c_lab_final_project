#include <stdio.h>
#include <stdlib.h>
#include "../../header_files/preprocessor/preprocessor_helper.h"

void preprocessor(char *file_name) {
  char line[80];

  char *as_file_name = get_file_name(file_name, ".an");
  char *an_file_name = get_file_name(file_name, ".an");

  printf("as file:%s \n", as_file_name);

  free(as_file_name);
  free(an_file_name);
}