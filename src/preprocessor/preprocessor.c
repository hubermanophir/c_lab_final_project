#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_file_name(char *file_name, char extention[4]) {

  int length = strlen(file_name);

  char *new_file_name = malloc(length + 4);

  strcpy(new_file_name, file_name);

  strcat(new_file_name, extention);

  return new_file_name;
}

void preprocessor(char *file_name) {
  char line[80];

  char *as_file_name = get_file_name(file_name, ".an");
  char *an_file_name = get_file_name(file_name, ".an");

  printf("as file:%s \n", as_file_name);

  free(as_file_name);
  free(an_file_name);
}