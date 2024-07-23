#include "../../../header_files/front/process_lines.h"
#include "../../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_symbol(void *symbol) {
  Symbol *s = (Symbol *)symbol;
  free(s->name);
  free(s);
}

void first_pass(FILE *am_file, int *is_valid_file,
                Translation_Unit *translation_unit) {
  int ic = 0, dc = 0, i, is_entry, line_number = 1, existing_symbols_size;
  Ent *current_entry;
  Extern *current_external;
  char line[MAX_LINE_LENGTH];
  Line_obj *current_line;
  Symbol *symbol;
  Symbol **existing_symbols;
  Ent **existing_entries;
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
        if (symbol->symbol_type == entry) {
          symbol->symbol_type =
              current_line->LineType == INSTRUCTION ? ent_code : ent_data;
          symbol->address = current_line->LineType == INSTRUCTION ? ic : dc;
        } else if (symbol->symbol_type == external) {
          printf("Line:%d, Error: Label %s external but declared in file\n",
                 current_line->line_number, current_line->label);
          *is_valid_file = 0;
          free(current_line);
          continue;

        } else {
          printf("Line:%d, Error: Label %s already declared\n",
                 current_line->line_number, current_line->label);
          *is_valid_file = 0;
          free(current_line);
          continue;
        }

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
      } else {
        ic += current_line->line_type.instruction.length;
      }
    } else {
      switch (current_line->line_type.directive.directive_option) {
      case DATA:
        for (i = 0;
             i <
             current_line->line_type.directive.directive_operand.data.length;
             i++) {
          translation_unit->data_image[dc + i] =
              current_line->line_type.directive.directive_operand.data
                  .numbers[i];
        }
        dc += current_line->line_type.directive.directive_operand.data.length;
        break;
      case STRING:
        for (i = 0;
             i <
             strlen(current_line->line_type.directive.directive_operand.string);
             i++) {

          translation_unit->data_image[dc + i] =
              current_line->line_type.directive.directive_operand.string[i];
        }
        translation_unit->data_image[dc + i] = '\0';
        dc +=
            strlen(current_line->line_type.directive.directive_operand.string) +
            1;
        break;
      case ENTRY:
      case EXTERN:
        is_entry = current_line->line_type.directive.directive_option == ENTRY;
        symbol = (Symbol *)get_by_name_field_hashtable(
            translation_unit->symbols_table,
            current_line->line_type.directive.directive_operand.label);
        if (symbol) {
          if (!is_entry) {
            printf("Line:%d, Error: Label %s external but declared in file\n",
                   current_line->line_number,
                   current_line->line_type.directive.directive_operand.label);
            *is_valid_file = 0;
            free(current_line);
            continue;
          } else {
            symbol->symbol_type =
                symbol->symbol_type == code ? ent_code : ent_data;
          }

        } else {
          symbol = (Symbol *)malloc(sizeof(Symbol));
          symbol->name = make_char_copy(
              current_line->line_type.directive.directive_operand.label);
          symbol->symbol_type = is_entry ? entry : external;
          symbol->address = 0;
          put_hashtable(translation_unit->symbols_table, symbol->name, symbol);
        }

        break;
      }
      translation_unit->dc = dc;
    }

    free(current_line);
  }

  /*After checking all the lines and having the symbol table and the ic, dc and
   * data_image filled*/
  existing_symbols_size = get_existing_values(translation_unit->symbols_table,
                                              (void ***)&existing_symbols);

  for (i = 0; i < existing_symbols_size; i++) {
    symbol = existing_symbols[i];

    if (symbol->symbol_type == entry) {
      printf("Error: Label %s entry but not declared in file\n", symbol->name);
      *is_valid_file = 0;
      continue;
    } else if (symbol->symbol_type == data || symbol->symbol_type == ent_data) {
      symbol->address += ic;
    }
    if (symbol->symbol_type == ent_data || symbol->symbol_type == ent_code) {
      current_entry = (Ent *)malloc(sizeof(Ent));
      current_entry->name = make_char_copy(symbol->name);
      current_entry->address = symbol->address + START_ADDRESS;
      put_hashtable(translation_unit->entries, current_entry->name,
                    current_entry);
    }
    if (symbol->symbol_type == external) {
      current_external = (Extern *)malloc(sizeof(Extern));
      current_external->name = make_char_copy(symbol->name);
      current_external->addresses_count = 0;
      put_hashtable(translation_unit->externals, current_external->name,
                    current_external);
    }
  }
  translation_unit->entries_count = get_existing_values(
      translation_unit->symbols_table, (void ***)&existing_entries);

  translation_unit->dc = dc;
  translation_unit->ic = 0;
  free(existing_symbols);
  free(existing_entries);
}