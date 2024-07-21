#include "../../header_files/data_structures/linked_list.h"
#include "../../header_files/middle/first_pass/first_pass.h"


void middle(LinkedList *lines, int *is_valid_file) {
  Translation_Unit translation_unit = {0};
  first_pass(lines, is_valid_file, &translation_unit);
  
}