#ifndef FILE_ASSEMBLER_H
#define FILE_ASSEMBLER_H
#include "../global.h"

/**
 * @brief Gets the translation units and exporting the ob, ext, ent files
 * 
 * @param translation_unit 
 * @param file_name 
 */
void file_assembler(Translation_Unit *translation_unit, char *file_name);

#endif