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
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) {
      return MIN_VALUE;
    }
  }
  return convert_number_str_to_int(str);
}

int is_valid_reg_num(char *str) {
  int num = is_number(str);
  if (num == MIN_VALUE) {
    return 0;
  }
  if (num < 0 || num > 7) {
    return 0;
  }
  return 1;
}

int is_comma_str(char *str) { return *str == ','; }
