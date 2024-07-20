#include "../../header_files/front/helper_functions.h"
#include "../../header_files/global.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Checks data array is valid and updates the line object
 *
 * @param line_obj
 * @param tokens_obj
 */
static void data_directive(Line_obj *line_obj, Tokens_Obj *tokens_obj) {
  int numbers[MAX_DATA_SIZE];
  int i, current_value, numbers_index = 0;

  for (i = 0; i < tokens_obj->size; i++) {

    if (i % 2 == 0) {
      current_value = is_number(tokens_obj->tokens[i]);
      if (current_value == MIN_VALUE) {
        strcpy(line_obj->error, "Invalid number");
        return;
      }
      numbers[numbers_index++] = current_value;
    } else {

      if (strcmp(tokens_obj->tokens[i], ",") != 0) {
        strcpy(line_obj->error, "Missing comma between numbers");
        return;
      }
    }
  }

  /*Got to this point only if there were no errors*/
  line_obj->line_type.directive.directive_operand.data.length = numbers_index;
  for (i = 0; i < numbers_index; i++) {
    line_obj->line_type.directive.directive_operand.data.numbers[i] =
        numbers[i];
  }
}

static void string_directive(Line_obj *line_obj, char *line) {
  char string[MAX_LINE_LENGTH];
  char *beginning_ptr, *end_ptr;
  int str_length;
  beginning_ptr = strpbrk(line, "\"");
  if (beginning_ptr == NULL) {
    strcpy(line_obj->error, "String not contained in quotes");
    return;
  }
  line = beginning_ptr + 1;
  end_ptr = strpbrk(line, "\"");
  if (end_ptr == NULL) {
    strcpy(line_obj->error, "String missing quotes");
    return;
  }
  str_length = end_ptr - line;
  strncpy(string, line, end_ptr - line);
  string[str_length] = '\0';

  strcpy(line_obj->line_type.directive.directive_operand.string, string);
}

void validate_and_update_directive(Line_obj *line_obj, char *line,
                                   Directive directive,
                                   Tokens_Obj *tokens_obj) {
  switch (directive) {
    /*Is an array of numbers separated by commas*/
  case DATA:
    data_directive(line_obj, tokens_obj);
    break;
    /*String contained in quotes "test string" */
  case STRING:
    string_directive(line_obj, line);
    break;
    /*Label declaration*/
  case ENTRY:
    break;
    /*External label declaration*/
  case EXTERN:
    break;
  }
}