#ifndef MACRO_ANALYZER_H
#define MACRO_ANALYZER_H

#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/preprocessor.h"

typedef enum MacroLineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE,
  SKIP_LINE,
  INVALID
} MacroLineType;

/**
 * @brief Analyzing the line to determine the type of line
 * 
 * @param line 
 * @param existing_macros 
 * @param current_macro 
 * @return MacroLineType 
 */
MacroLineType get_line_type(char *line, Hashtable *existing_macros, Macro *current_macro);

#endif