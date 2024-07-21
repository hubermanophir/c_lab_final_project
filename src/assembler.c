
#include "../header_files/front/front.h"
#include "../header_files/middle/middle.h"
#include "../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  LinkedList *lines;
  int i, is_valid_file = 1;
  argc--;
  argv++;
  for (i = 0; i < argc; i++) {
    printf("Processing file: %s.as\n", argv[i]);

    an_file_name = preprocessor(argv[i]);
    if (!an_file_name) {
      free(an_file_name);
      continue;
    }

    lines = get_processed_lines(an_file_name);

    middle(lines, &is_valid_file);

    if (!is_valid_file) {
      free(an_file_name);
      free_list(lines, free);
      continue;
    }
    printf("%s.as is valid\n", argv[i]);

    free(an_file_name);
    free_list(lines, free);
  }

  return 0;
}
