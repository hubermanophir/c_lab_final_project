#include "../../header_files/data_structures/linked_list.h"
#include "../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char **separate_line_to_chars_by_spaces(char *line) {
  char **tokens = (char **)malloc(sizeof(char *) * MAX_LINE_LENGTH);
  char *tok;
  int i = 0;

  if (tokens == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  return tokens;
}

static Line_obj *process_single_line(char *line) {
  char *lineptr = line, *tok, label[MAX_LABEL_LENGTH],
       test_str[MAX_LINE_LENGTH];
  Line_obj *line_obj;
  int last_ptr;
  int is_label_declaration;
  Opcode opcode;
  Directive directive;

  line_obj = (Line_obj *)malloc(sizeof(Line_obj));
  if (line_obj == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  /*Trim line end and beginning white chars*/
  lineptr[strlen(lineptr) - 1] = '\0';
  SKIP_WHITESPACE(lineptr);
  trim_trailing_whitespace(lineptr);

  tok = strpbrk(lineptr, SPACE_CHARS);
  if (tok == NULL) {
    free(line_obj);
    return NULL;
  }
  last_ptr = tok - lineptr;

  strncpy(test_str, lineptr, last_ptr);
  test_str[last_ptr] = '\0';
  opcode = get_opcode_from_string(test_str);
  directive = get_directive_from_string(test_str);

  if (opcode != -1) {
    printf("line opcode: %d , line: %s\n", opcode, line);
  } else if (directive != -1) {
    printf("line directive: %d line: %s\n", directive, line);
  } else {
    printf("Non of the above line: %s is delaration:%d\n", line,
           is_label_declaration);
  }
  return line_obj;
}

void process_lines(FILE *am_file, LinkedList *lines) {
  char line[MAX_LINE_LENGTH];
  Line_obj *line_obj;

  while (fgets(line, MAX_LINE_LENGTH, am_file)) {
    line_obj = process_single_line(line);
    if (line_obj) {
      free(line_obj);
    } else {
      free(line_obj);
    }
  }
}