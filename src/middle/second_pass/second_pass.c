#include "../../../header_files/front/process_lines.h"
#include "../../../header_files/global.h"
#include <stdio.h>
#include <stdlib.h>

void printBinary15Bits(int number) {
  int i, bit;
  for (i = 14; i >= 0; i--) {
    bit = (number >> i) & 1;
    printf("%d", bit);
  }
  printf("\n");
}

void add_ARE(ARE are, int *code_line) { *code_line |= are; }

void add_code_per_operand(Translation_Unit *translation_unit, int *code_image,
                          Line_obj *current_line, int index,
                          int *is_valid_file) {
  Symbol *symbol;
  AddressingMode addressing_mode =
      current_line->line_type.instruction.addressing[index];
  Extern *existing_external;
  translation_unit->ic++;
  switch (addressing_mode) {
  case IMMEDIATE:
    code_image[translation_unit->ic] |=
        current_line->line_type.instruction.operands[index].immediate << 3;
    add_ARE(A, &translation_unit->code_image[translation_unit->ic]);

    break;
  case DIRECT:
    symbol = get_by_name_field_hashtable(
        translation_unit->symbols_table,
        current_line->line_type.instruction.operands[index].label);
    if (symbol) {
      if (symbol->symbol_type == external) {
        add_ARE(E, &translation_unit->code_image[translation_unit->ic]);
        existing_external = get_by_name_field_hashtable(
            translation_unit->externals, symbol->name);
        existing_external->addresses[existing_external->addresses_count++] =
            translation_unit->ic + START_ADDRESS;
        break;
      } else {
        code_image[translation_unit->ic] |= (symbol->address + START_ADDRESS)
                                            << 3;
        add_ARE(R, &translation_unit->code_image[translation_unit->ic]);
        break;
      }
    } else {
      *is_valid_file = 0;
      printf("Error: Line %d: %s is not defined\n", current_line->line_number,
             current_line->line_type.instruction.operands[index].label);
    }
    break;
  case INDIRECT_ACCUMULATE:
  case DIRECT_ACCUMULATE:
    code_image[translation_unit->ic] |=
        current_line->line_type.instruction.operands[index].register_index << 3;
    add_ARE(A, &translation_unit->code_image[translation_unit->ic]);
    break;
  default:
    break;
  }
}

void add_to_code_image(Translation_Unit *translation_unit, int *code_image,
                       Line_obj *current_line, int *is_valid_file) {
  int operand_length = current_line->line_type.instruction.length;
  translation_unit->code_image[translation_unit->ic] =
      current_line->line_type.instruction.opcode_option << 11;

  add_ARE(A, &translation_unit->code_image[translation_unit->ic]);
  if (operand_length == 2) {
    translation_unit->code_image[translation_unit->ic] |=
        current_line->line_type.instruction.addressing[0] << 7;
    translation_unit->code_image[translation_unit->ic] |=
        current_line->line_type.instruction.addressing[1] << 3;

    if (is_register(current_line->line_type.instruction.addressing[0]) &&
        is_register(current_line->line_type.instruction.addressing[1])) {
      translation_unit->ic++;
      code_image[translation_unit->ic] |=
          current_line->line_type.instruction.operands[0].register_index << 6;
      code_image[translation_unit->ic] |=
          current_line->line_type.instruction.operands[1].register_index << 3;
      add_ARE(A, &translation_unit->code_image[translation_unit->ic]);
      return;
    }
    add_code_per_operand(translation_unit, code_image, current_line, 0,
                         is_valid_file);
    add_code_per_operand(translation_unit, code_image, current_line, 1,
                         is_valid_file);
  } else if (operand_length == 1) {
    translation_unit->code_image[translation_unit->ic] |=
        current_line->line_type.instruction.addressing[0] << 3;

    add_code_per_operand(translation_unit, code_image, current_line, 0,
                         is_valid_file);
  }
}

void second_pass(FILE *am_file, int *is_valid_file,
                 Translation_Unit *translation_unit, char *file_name) {
  int line_number = 1;
  char line[MAX_LINE_LENGTH];
  Line_obj *current_line;

  while (fgets(line, MAX_LINE_LENGTH, am_file)) {
    current_line = process_single_line(line, line_number++);
    if (current_line->LineType == INSTRUCTION) {
      add_to_code_image(translation_unit, translation_unit->code_image,
                        current_line, is_valid_file);
      translation_unit->ic++;
    }
    free(current_line);
  }
}