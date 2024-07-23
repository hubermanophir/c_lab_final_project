#include "../../header_files/global.h"
#include "../../header_files/preprocessor/helper.h"
#include <stdio.h>
#include <stdlib.h>

#define OBJECT_FILE_EXTENSION ".ob"
#define ENTRY_FILE_EXTENSION ".ent"
#define EXTERN_FILE_EXTENSION ".ext"

/**
 * @brief Takes a number and converts it to a 5 base number
 * meaning takes something like this in binary  = 001010000010100 and converts to 12024
 * @param file 
 * @param number 
 */
static void convert_15_to_5(FILE *file, int number) {
    int i, bit, count = 0, result = 0;
    for (i = 14; i >= 0; i--) {
        bit = (number >> i) & 1;
        result = (result << 1) | bit;
        count++;
        if (count == 3) {
            fprintf(file, "%d", result);
            count = 0;
            result = 0;
        }
    }
}

void file_assembler(Translation_Unit *translation_unit, char *file_name) {
  Ent **existing_entries;
  Extern **existing_externs;
  char *obj_file_name, *ent_file_name, *ext_file_name;
  FILE *obj_file, *ent_file, *ext_file;
  int ic = translation_unit->ic, dc = translation_unit->dc, entries_size,
      externs_size;
  int *code_image = translation_unit->code_image,
      *data_image = translation_unit->data_image;
  int i, j;
  entries_size = get_existing_values(translation_unit->entries,
                                     (void ***)&existing_entries);
  externs_size = get_existing_values(translation_unit->externals,
                                     (void ***)&existing_externs);

  obj_file_name = get_file_name(file_name, OBJECT_FILE_EXTENSION);
  ent_file_name = get_file_name(file_name, ENTRY_FILE_EXTENSION);
  ext_file_name = get_file_name(file_name, EXTERN_FILE_EXTENSION);

  obj_file = fopen(obj_file_name, "w");
  ent_file = fopen(ent_file_name, "w");
  ext_file = fopen(ext_file_name, "w");

  if (!obj_file || !ent_file || !ext_file) {
    free(obj_file_name);
    free(ent_file_name);
    free(ext_file_name);
    free(existing_entries);
    free(existing_externs);
    return;
  }

  for (i = 0; i < entries_size; i++) {
    fputs(existing_entries[i]->name, ent_file);
    fputs("\t", ent_file);
    fprintf(ent_file, "%d", existing_entries[i]->address);
    fputs("\n", ent_file);
  }

  for (i = 0; i < externs_size; i++) {
    for (j = 0; j < existing_externs[i]->addresses_count; j++) {
      fputs(existing_externs[i]->name, ext_file);
      fputs("\t", ext_file);
      fprintf(ext_file, "0%d", existing_externs[i]->addresses[j]);
      fputs("\n", ext_file);
    }
  }

  fprintf(obj_file, "  %d\t%d\n", ic, dc);
  for (i = 0; i < ic; i++) {
    fprintf(obj_file, "0%d\t", i + START_ADDRESS);
    convert_15_to_5(obj_file, code_image[i]);
    fputs("\n", obj_file);
  }

  for (i = 0; i < dc; i++) {
    fprintf(obj_file, "0%d\t", i + ic + START_ADDRESS);
    convert_15_to_5(obj_file, data_image[i]);
    fputs("\n", obj_file);
  }

  fclose(obj_file);
  fclose(ent_file);
  fclose(ext_file);
  free(obj_file_name);
  free(ent_file_name);
  free(ext_file_name);
  free(existing_entries);
  free(existing_externs);
}