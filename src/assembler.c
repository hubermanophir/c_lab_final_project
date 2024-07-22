
#include "../header_files/front/front.h"
#include "../header_files/middle/middle.h"
#include "../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  LinkedList *lines;
  Hashtable *symbols_table;
  Translation_Unit translation_unit = {0};
  int i, is_valid_file;
  argc--;
  argv++;
  for (i = 0; i < argc; i++) {
    is_valid_file = 1;
    printf("Processing file: %s.as\n", argv[i]);

    an_file_name = preprocessor(argv[i]);
    if (!an_file_name) {
      free(an_file_name);
      continue;
    }

    lines = get_processed_lines(an_file_name);
    symbols_table = create_hashtable(100);
    if (symbols_table == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    translation_unit.symbols_table = symbols_table;
    middle(lines, &is_valid_file, &translation_unit);

    if (!is_valid_file) {
      free(an_file_name);
      free_list(lines, free);
      free_hashtable(symbols_table, free);
      continue;
    }
    printf("%s.as is valid\n", argv[i]);

    free(an_file_name);
    free_list(lines, free);
    free_hashtable(symbols_table, free);
  }

  return 0;
}
