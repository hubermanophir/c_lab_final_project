#include "../../../header_files/front/process_lines.h"
#include "../../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_register(AddressingMode addressing) {
  return addressing == DIRECT_ACCUMULATE || addressing == INDIRECT_ACCUMULATE;
}

void free_symbol(void *symbol) {
  Symbol *s = (Symbol *)symbol;
  free(s->name);
  free(s);
}

/*Should check validity of labels
populate the data_image using DC
.data, .string addresses should be by dc
Then offset them them by the IC
*/
void first_pass(FILE *am_file, int *is_valid_file,
                Translation_Unit *translation_unit) {
  int ic = 0, dc = 0;
  char line[MAX_LINE_LENGTH];
  int line_number = 1;
  Line_obj *current_line;
  Symbol *symbol;
  while (fgets(line, MAX_LINE_LENGTH, am_file)) {
    current_line = process_single_line(line, line_number++);
    /*Check error of line conversion*/
    if (current_line->LineType == ERROR) {
      printf("Line:%d, Error: %s\n", current_line->line_number,
             current_line->error);
      *is_valid_file = 0;
      free(current_line);
      continue;
    }

    /*There is a label declaration in the line*/
    if (strcmp(current_line->label, "") != 0 &&
        (current_line->LineType == INSTRUCTION ||
         (current_line->LineType == DIRECTIVE &&
          ((current_line->line_type.directive.directive_option == DATA) ||
           current_line->line_type.directive.directive_option == STRING)))) {
      symbol = (Symbol *)get_by_name_field_hashtable(
          translation_unit->symbols_table, current_line->label);
      if (symbol) {
        printf("Line:%d, Error: Label %s already declared\n",
               current_line->line_number, current_line->label);
        *is_valid_file = 0;
        free(current_line);
        continue;
      } else {
        symbol = (Symbol *)malloc(sizeof(Symbol));
        if (symbol == NULL) {
          printf("Memory allocation failed\n");
          exit(1);
        }

        symbol->name = make_char_copy(current_line->label);
        if (current_line->LineType == INSTRUCTION) {
          symbol->symbol_type = code;
          symbol->address = ic;
        } else {
          symbol->symbol_type = data;
          symbol->address = dc;
        }
        put_hashtable(translation_unit->symbols_table, symbol->name, symbol);
      }
    }

    if (current_line->LineType == INSTRUCTION) {
      ic++;
      if (is_register(current_line->line_type.instruction.addressing[0]) &&
          is_register(current_line->line_type.instruction.addressing[1])) {
        ic++;
      }
    }
    free(current_line);
  }
}