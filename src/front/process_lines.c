#include "../../header_files/front/front_validations.h"
#include "../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief separate the line into tokens by space chars and commas
 *
 * @param line
 * @return char**
 */
Tokens_Obj tokenize(char *line) {
  Tokens_Obj tokens_obj = {0};
  int size = 0;
  char *tok;

  if (*line == '\n') {
    return tokens_obj;
  }

  do {
    if (*line == ',') {
      tokens_obj.tokens[size++] = ",";
      line++;
      SKIP_WHITESPACE(line);
      continue;
    }
    tokens_obj.tokens[size++] = line;
    tok = strpbrk(line, SPACE_CHARS ",");
    if (tok) {
      if (*tok == ',') {
        *tok = '\0';
        tok++;
        tokens_obj.tokens[size++] = ",";
        SKIP_WHITESPACE(tok);
        line = tok;
      } else {
        *tok = '\0';
        tok++;
        SKIP_WHITESPACE(tok);
        line = tok;
      }
    } else {
      break;
    }

  } while (*line && size < MAX_LINE_LENGTH);

  tokens_obj.size = size;
  return tokens_obj;
}
union directive_or_opcode {
  Directive directive;
  Opcode opcode;
} directive_or_opcode;

Directive is_directive_in_tokens(Tokens_Obj tokens_obj) {
  int i;
  Directive directive;
  for (i = 0; i < tokens_obj.size; i++) {
    directive = get_directive_from_string(tokens_obj.tokens[i]);
    if (directive != -1) {
      return 1;
    }
  }
  return 0;
}

Opcode is_opcode_in_tokens(Tokens_Obj tokens_obj) {
  int i;
  Opcode opcode;
  for (i = 0; i < tokens_obj.size; i++) {
    opcode = get_opcode_from_string(tokens_obj.tokens[i]);
    if (opcode != -1) {
      return 1;
    }
  }
  return 0;
}

Line_obj *process_single_line(char *line, int line_number) {
  Line_obj *line_obj;
  Tokens_Obj tokens_obj;
  char line_copy[MAX_LINE_LENGTH];
  int is_directive, is_opcode;

  line_obj = (Line_obj *)malloc(sizeof(Line_obj));
  if (line_obj == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  line_obj->line_number = line_number;

  if (strlen(line) > 0) {
    line[strlen(line) - 1] = '\0';
    trim_trailing_whitespace(line);
    SKIP_WHITESPACE(line);
  }

  strcpy(line_copy, line);
  tokens_obj = tokenize(line);

  is_directive = is_directive_in_tokens(tokens_obj);
  is_opcode = is_opcode_in_tokens(tokens_obj);

  if (is_directive && is_opcode) {
    strcpy(line_obj->error, "Error: line contains both directive and opcode");
    line_obj->LineType = ERROR;
    return line_obj;
  } else if (is_directive) {
    line_obj->LineType = DIRECTIVE;
    validate_directive_line(&tokens_obj, line_obj, line_copy);
    return line_obj;

  } else if (is_opcode) {
    line_obj->LineType = INSTRUCTION;
    validate_instruction_line(&tokens_obj, line_obj);
    return line_obj;
  }
  strcpy(line_obj->error, "Error: File non of the allowed types: comment, "
                          "empty, directive, instruction");
  line_obj->LineType = ERROR;

  return line_obj;
}