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
 
.PHONY: clean build_env all folder_clean
 
all: build_env $(PROG_NAME) 
 
$(PROG_NAME):  assembler.o process_lines.o second_pass.o middle.o file_assembler.o first_pass.o helper_functions.o directive_line_validations.o instruction_line_validations.o hashtable.o linked_list.o global.o helper.o macro.o macro_line_analyzer.o preprocessor.o front_validations.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@
 
assembler.o: src/assembler.c \
 src/../header_files/file_assembler/file_assembler.h \
 src/../header_files/file_assembler/../global.h \
 src/../header_files/file_assembler/../data_structures/hashtable.h \
 src/../header_files/file_assembler/../data_structures/linked_list.h \
 src/../header_files/middle/middle.h \
 src/../header_files/middle/../data_structures/linked_list.h \
 src/../header_files/middle/../global.h \
 src/../header_files/middle/./first_pass/first_pass.h \
 src/../header_files/middle/./first_pass/../../global.h \
 src/../header_files/preprocessor/preprocessor.h
hashtable.o: src/data_structures/hashtable.c \
 src/data_structures/../../header_files/preprocessor/macro.h \
 src/data_structures/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h
linked_list.o: src/data_structures/linked_list.c
file_assembler.o: src/file_assembler/file_assembler.c \
 src/file_assembler/../../header_files/global.h \
 src/file_assembler/../../header_files/data_structures/hashtable.h \
 src/file_assembler/../../header_files/data_structures/linked_list.h
directive_line_validations.o: src/front/directive_line_validations.c \
 src/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/front/../data_structures/hashtable.h \
 src/front/../../header_files/front/../data_structures/linked_list.h \
 src/front/../../header_files/global.h
front_validations.o: src/front/front_validations.c \
 src/front/../../header_files/front/directive_line_validations.h \
 src/front/../../header_files/front/../front/helper_functions.h \
 src/front/../../header_files/front/../front/../global.h \
 src/front/../../header_files/front/../front/../data_structures/hashtable.h \
 src/front/../../header_files/front/../front/../data_structures/linked_list.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/front/instruction_line_validations.h \
 src/front/../../header_files/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/front/../../header_files/global.h \
 src/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/global.h
helper_functions.o: src/front/helper_functions.c \
 src/front/../../header_files/global.h \
 src/front/../../header_files/data_structures/hashtable.h \
 src/front/../../header_files/data_structures/linked_list.h
instruction_line_validations.o: src/front/instruction_line_validations.c \
 src/front/../../header_files/front/helper_functions.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/front/../data_structures/hashtable.h \
 src/front/../../header_files/front/../data_structures/linked_list.h \
 src/front/../../header_files/front/validation_types.h \
 src/front/../../header_files/global.h
process_lines.o: src/front/process_lines.c \
 src/front/../../header_files/front/front_validations.h \
 src/front/../../header_files/front/../global.h \
 src/front/../../header_files/front/../data_structures/hashtable.h \
 src/front/../../header_files/front/../data_structures/linked_list.h \
 src/front/../../header_files/global.h
global.o: src/global.c src/../header_files/global.h \
 src/../header_files/data_structures/hashtable.h \
 src/../header_files/data_structures/linked_list.h
first_pass.o: src/middle/first_pass/first_pass.c \
 src/middle/first_pass/../../../header_files/front/process_lines.h \
 src/middle/first_pass/../../../header_files/front/../../header_files/global.h \
 src/middle/first_pass/../../../header_files/front/../../header_files/data_structures/hashtable.h \
 src/middle/first_pass/../../../header_files/front/../../header_files/data_structures/linked_list.h \
 src/middle/first_pass/../../../header_files/global.h
middle.o: src/middle/middle.c \
 src/middle/../../header_files/middle/first_pass/first_pass.h \
 src/middle/../../header_files/middle/first_pass/../../global.h \
 src/middle/../../header_files/middle/first_pass/../../data_structures/hashtable.h \
 src/middle/../../header_files/middle/first_pass/../../data_structures/linked_list.h \
 src/middle/../../header_files/middle/second_pass/second_pass.h \
 src/middle/../../header_files/middle/second_pass/../../global.h
second_pass.o: src/middle/second_pass/second_pass.c \
 src/middle/second_pass/../../../header_files/front/process_lines.h \
 src/middle/second_pass/../../../header_files/front/../../header_files/global.h \
 src/middle/second_pass/../../../header_files/front/../../header_files/data_structures/hashtable.h \
 src/middle/second_pass/../../../header_files/front/../../header_files/data_structures/linked_list.h \
 src/middle/second_pass/../../../header_files/global.h
helper.o: src/preprocessor/helper.c
macro.o: src/preprocessor/macro.c \
 src/preprocessor/../../header_files/data_structures/linked_list.h
macro_line_analyzer.o: src/preprocessor/macro_line_analyzer.c \
 src/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/data_structures/linked_list.h \
 src/preprocessor/../../header_files/preprocessor/Macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h
preprocessor.o: src/preprocessor/preprocessor.c \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/data_structures/linked_list.h \
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
	find . -type f -name '*.an' -delete
	find . -type f -name '*.ob' -delete
	find . -type f -name '*.ent' -delete
	find . -type f -name '*.ext' -delete
 
folder_clean:
	find . -type f -name '*.an' -delete
	find . -type f -name '*.ob' -delete
	find . -type f -name '*.ent' -delete
	find . -type f -name '*.ext' -delete

build_env:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
 
zip: clean
	rm -f $(ZIP_NAME)
	zip -r $(ZIP_NAME) *

##gcc -MM $(find ./ -type f -name '*.c' -printf '%P\n') >> makefile
