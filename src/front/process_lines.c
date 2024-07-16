#include "../../header_files/data_structures/linked_list.h"
#include "../../header_files/global.h"
#include <stdio.h>
#include <string.h>

static Line_obj process_single_line(char *line) {
  char *tok;
  tok = line;
  tok[strlen(tok) - 1] = '\0';
  SKIP_WHITESPACE(tok);
  trim_trailing_whitespace(tok);
  printf("%s\n", tok);
}

void process_lines(FILE *am_file, LinkedList *lines) {
  char line[MAX_LINE_LENGTH];

  while (fgets(line, MAX_LINE_LENGTH, am_file)) {
    process_single_line(line);
  }
}