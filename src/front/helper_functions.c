#include "../../header_files/global.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int convert_number_str_to_int(char *str) {
  char *endptr;
  int num = strtol(str, &endptr, 10);
  if (*endptr != '\0') {
    return 0;
  }
  return num;
}

int is_number(char *str) {
  int i = 0;
  int is_negative = str[0] == '-' ? 1 : 0;
  int is_plus = str[0] == '+' ? 1 : 0;
  if (is_negative || is_plus) {
    i++;
  }
  for (; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return MIN_VALUE;
    }
  }
  return (is_negative ? -1 : 1) *
         convert_number_str_to_int(str + is_negative + is_plus);
}

int is_valid_reg_num(char *str, Line_obj *line_obj) {
  int num = is_number(str);
  if (num == MIN_VALUE) {
    return 0;
  }

  if (num < 0 || num > 7) {
    strcpy(line_obj->error, "Invalid register number");
    return 0;
  }
  return 1;
}

int is_comma_str(char *str) { return *str == ','; }
