
#include "../header_files/front/front.h"
#include "../header_files/preprocessor/preprocessor.h"
#include "../header_files/global.h"

#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  LinkedList *lines;
  Line_obj *current_line;

  an_file_name = preprocessor(argv[1]);
  if (!an_file_name) {
    exit(1);
  }

  lines = get_processed_lines(an_file_name);


  free(an_file_name);

  free_list(lines, free);

  return 0;
}
