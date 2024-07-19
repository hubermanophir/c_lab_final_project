
#include "../header_files/front/front.h"
#include "../header_files/global.h"
#include "../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char *an_file_name;
  char *line_error;
  LinkedList *lines;
  Node *current_list_item;

  an_file_name = preprocessor(argv[1]);
  if (!an_file_name) {
    exit(1);
  }

  lines = get_processed_lines(an_file_name);

  current_list_item = lines->head;

  while (current_list_item) {
    line_error = ((Line_obj *)current_list_item->data)->error;
    if (strcmp(line_error, "") != 0) {
      printf("Line:%d, Error: %s\n",
             ((Line_obj *)current_list_item->data)->line_number, line_error);
    }
    current_list_item = current_list_item->next;
  }

  free(an_file_name);

  free_list(lines, free);

  return 0;
}
