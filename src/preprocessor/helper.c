
#include <stdlib.h>
#include <string.h>

char *get_file_name(char *file_name, char extention[6]) {
  char *new_file_name = malloc(strlen(file_name) + 6);

  strcpy(new_file_name, file_name);
  strcat(new_file_name, extention);

  return new_file_name;
}