#include "../../header_files/data_structures/linked_list.h"
#include "../../header_files/front/process_lines.h"
#include <stdio.h>

LinkedList *get_processed_lines(char *filename) {
  FILE *am_file;
  LinkedList *lines;

  lines = init_list();

  am_file = fopen(filename, "r");
  process_lines(am_file, lines);
  return lines;
}