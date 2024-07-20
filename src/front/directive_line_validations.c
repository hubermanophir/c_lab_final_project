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
    break;
    /*Label declaration*/
  case ENTRY:
    break;
    /*External label declaration*/
  case EXTERN:
    break;
  }
}