#include <stdio.h>
#include <string.h>

void preprocessor(char *file_name) {
  char line[80];

  char *as_file_name = strcat(strcpy("", file_name), ".as");
  char *am_file_name = strcat(strcpy("", file_name), ".am");

  printf("as file:%s am file:%s", as_file_name, am_file_name);
}