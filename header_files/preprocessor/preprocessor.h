char *preprocessor(char *file_name);

typedef enum LineType {
  MACRO_DECLARATION,
  MACRO_END,
  MACRO_CALL,
  CODE_LINE
} LineType;

