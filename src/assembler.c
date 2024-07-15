#include "../header_files/preprocessor/preprocessor.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  printf("argv %s\n", argv[1]);
  an_file_name = preprocessor(argv[1]);
  if (!an_file_name) {
    printf("Error");
    exit(1);
  }
  free(an_file_name);
  return 0;
}
