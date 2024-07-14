#ifndef MACRO_ANALYZER_H
#define MACRO_ANALYZER_H

#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/preprocessor/macro.h"
#include "../../header_files/preprocessor/preprocessor.h"

typedef enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
} LineType;

LineType get_line_type(char *line, Hashtable *existing_macros);

#endif