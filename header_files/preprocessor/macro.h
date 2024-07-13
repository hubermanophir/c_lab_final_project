#include "../../header_files/data_structures/hashtable.h"
#include "../../header_files/data_structures/linked_list.h"

typedef struct Macro {
  char *name;
  LinkedList *lines;
} Macro;

enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
};