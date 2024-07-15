#include "../header_files/data_structures/hashtable.h"
#include "../header_files/preprocessor/macro.h"
#include "../header_files/preprocessor/preprocessor.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  char *an_file_name;
  an_file_name = preprocessor(argv[1]);
  if (!an_file_name) {
    printf("Error");
    exit(1);
  }
  free(an_file_name);

  /*
  Macro *current_macro = NULL;
  Hashtable *macros = create_hashtable(100);
  current_macro = create_macro();
  add_macro_name(current_macro, "test");
  append_macro_line(current_macro, "test line");

  append_macro_line(current_macro, "test line");
  append_macro_line(current_macro, "test line");
  append_macro_line(current_macro, "test line");
  append_macro_line(current_macro, "test line");
  append_macro_line(current_macro, "test line");

  put_hashtable(macros, "test", current_macro);
  append_macro_line(current_macro, "test line");

  current_macro = NULL;
  current_macro = (Macro *)get_macro_hashtable(macros, "test");


  printf("macro name: %s\n", (char *)current_macro->name);
  free_macro_hashtable(macros);
  */
  return 0;
}
