
#include "../header_files/file_assembler/file_assembler.h"
#include "../header_files/middle/middle.h"
#include "../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  Hashtable *symbols_table;
  Translation_Unit translation_unit = {0};
  Hashtable *externals = NULL, *entries = NULL;
  FILE *am_file;
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

    symbols_table = create_hashtable(100);
    externals = create_hashtable(100);
    entries = create_hashtable(100);

    if (symbols_table == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    translation_unit.symbols_table = symbols_table;
    translation_unit.externals = externals;
    translation_unit.entries = entries;
    am_file = fopen(an_file_name, "r");

    middle(am_file, &is_valid_file, &translation_unit);

    if (!is_valid_file) {
      free(an_file_name);
      free_hashtable(entries, free_symbol);
      free_hashtable(externals, free_symbol);
      free_hashtable(symbols_table, free_symbol);
      continue;
    }

    file_assembler();
    printf("%s.as is valid\n", argv[i]);

    free(an_file_name);
    free_hashtable(entries, free_symbol);
    free_hashtable(externals, free_symbol);
    free_hashtable(symbols_table, free_symbol);
  }

  return 0;
}
