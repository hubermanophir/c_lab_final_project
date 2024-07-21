#include "../../../header_files/data_structures/linked_list.h"
#include "../../../header_files/global.h"
#include <stdio.h>

void first_pass(LinkedList *lines, int *is_valid_file) {
  int IC = 100, DC = 0;
  Node *current_node = lines->head;
  Line_obj *current_line;
  while (current_node) {
    current_line = (Line_obj *)current_node->data;
    if (current_line->LineType == ERROR) {
      printf("Line:%d, Error: %s\n", current_line->line_number,
             current_line->error);
      *is_valid_file = 0;
    }
    current_node = current_node->next;
  }
}