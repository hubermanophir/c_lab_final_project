
#include "../header_files/front/front.h"
#include "../header_files/global.h"
#include "../header_files/preprocessor/preprocessor.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char *an_file_name;
  char *line_error;
  LinkedList *lines;
  Node *current_list_item;
  int is_valid_file = 1;

  an_file_name = preprocessor(argv[1]);
  if (!an_file_name) {
    exit(1);
  }

  lines = get_processed_lines(an_file_name);

  current_list_item = lines->head;

  while (current_list_item) {
    line_error = ((Line_obj *)current_list_item->data)->error;
    if (((Line_obj *)current_list_item->data)->LineType == ERROR) {
      printf("Line:%d, Error: %s\n",
             ((Line_obj *)current_list_item->data)->line_number, line_error);
      is_valid_file = 0;
    }
    current_list_item = current_list_item->next;
  }
  if (!is_valid_file) {
    exit(1);
  }

  free(an_file_name);

  free_list(lines, free);

  return 0;
}
