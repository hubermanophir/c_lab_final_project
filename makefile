CC			= gcc
CFLAGS		= -ansi -pedantic -Wall
PROG_NAME 	= assembler
BUILD_DIR	= build
OBJ_DIR		= $(BUILD_DIR)/obj
BIN_DIR		= $(BUILD_DIR)/bin
ZIP_NAME	= mmn22.zip

ifdef DEBUG
CFLAGS += -g -fsanitize=address
endif
 
.PHONY: clean build_env all
 
all: build_env $(PROG_NAME) 
 
$(PROG_NAME):  assembler.o process_lines.o helper_functions.o directive_line_validations.o instruction_line_validations.o hashtable.o linked_list.o global.o helper.o macro.o macro_line_analyzer.o preprocessor.o front.o front_validations.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@
 
assembler.o: src/assembler.c src/../header_files/front/front.h \
 src/../header_files/front/../data_structures/linked_list.h \
 src/../header_files/front/../global.h src/../header_files/global.h \
 src/../header_files/preprocessor/preprocessor.h
hashtable.o: src/data_structures/hashtable.c \
 src/data_structures/../../header_files/preprocessor/macro.h \
 src/data_structures/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h
linked_list.o: src/data_structures/linked_list.c
directive_line_validations.o: src/front/directive_line_validations.c \
 src/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/global.h
front.o: src/front/front.c \
 src/front/../../header_files/data_structures/linked_list.h \
 src/front/../../header_files/front/process_lines.h \
 src/front/../../header_files/front/../../header_files/data_structures/linked_list.h \
 src/front/../../header_files/front/../../header_files/global.h
front_validations.o: src/front/front_validations.c \
 src/front/../../header_files/front/directive_line_validations.h \
 src/front/../../header_files/front/../front/helper_functions.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/front/instruction_line_validations.h \
 src/front/../../header_files/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/front/../../header_files/global.h \
 src/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/global.h
helper_functions.o: src/front/helper_functions.c \
 src/front/../../header_files/global.h
instruction_line_validations.o: src/front/instruction_line_validations.c \
 src/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/global.h
process_lines.o: src/front/process_lines.c \
 src/front/../../header_files/data_structures/linked_list.h \
 src/front/../../header_files/front/front_validations.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/global.h
global.o: src/global.c src/../header_files/global.h
helper.o: src/preprocessor/helper.c
macro.o: src/preprocessor/macro.c \
 src/preprocessor/../../header_files/data_structures/linked_list.h
macro_line_analyzer.o: src/preprocessor/macro_line_analyzer.c \
 src/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/preprocessor/Macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h
preprocessor.o: src/preprocessor/preprocessor.c \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/preprocessor/helper.h \
 src/preprocessor/../../header_files/preprocessor/macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h \
 src/preprocessor/../../header_files/preprocessor/macro_line_analyzer.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/preprocessor/macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/preprocessor/preprocessor.h

%.o:
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@
 
clean:
	rm -rf $(BUILD_DIR)
 
build_env:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
 
zip: clean
	rm -f $(ZIP_NAME)
	zip -r $(ZIP_NAME) *

##gcc -MM $(find ./ -type f -name '*.c' -printf '%P\n') >> makefile
