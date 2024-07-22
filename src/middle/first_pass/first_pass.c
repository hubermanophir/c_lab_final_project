#include "../../../header_files/data_structures/linked_list.h"
#include "../../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_register(AddressingMode addressing) {
  return addressing == DIRECT_ACCUMULATE || addressing == INDIRECT_ACCUMULATE;
}

/*Should check validity of labels
populate the data_image using DC
.data, .string addresses should be by dc
Then offset them them by the IC
*/
void first_pass(LinkedList *lines, int *is_valid_file,
                Translation_Unit *translation_unit) {
  int ic = 0, dc = 0;
  Node *current_node = lines->head;
  Line_obj *current_line;
  Symbol *symbol;
  while (current_node) {
    current_line = (Line_obj *)current_node->data;
    /*Check error of line conversion*/
    if (current_line->LineType == ERROR) {
      printf("Line:%d, Error: %s\n", current_line->line_number,
             current_line->error);
      *is_valid_file = 0;
    }

    /*There is a label declaration in the line*/
    if (strcmp(current_line->label, "") != 0 &&
        (current_line->LineType == INSTRUCTION ||
         (current_line->LineType == DIRECTIVE &&
          ((current_line->line_type.directive.directive_option == DATA) ||
           current_line->line_type.directive.directive_option == STRING)))) {
      symbol = (Symbol *)get_by_name_field_hashtable(
          translation_unit->symbols_table, current_line->label);
      if (symbol != NULL) {
        printf("Line:%d, Error: Label %s already declared\n",
               current_line->line_number, current_line->label);
        *is_valid_file = 0;
      } else {

        symbol = (Symbol *)malloc(sizeof(Symbol));
        if (symbol == NULL) {
          printf("Memory allocation failed\n");
          exit(1);
        }
        symbol->name = current_line->label;
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

    current_node = current_node->next;
  }
}