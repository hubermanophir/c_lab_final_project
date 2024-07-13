void preprocessor(char *file_name);

char *get_file_name(char *file_name);

typedef enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
} LineType;