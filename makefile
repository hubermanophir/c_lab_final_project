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
 
$(PROG_NAME):  assembler.o hashtable.o linked_list.o global.o helper.o macro.o macro_line_analizer.o preprocessor.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@
 

assembler.o: src/assembler.c \
 src/../header_files/preprocessor/preprocessor.h
hashtable.o: src/data_structures/hashtable.c \
 src/data_structures/../../header_files/data_structures/hashtable.h
linked_list.o: src/data_structures/linked_list.c \
 src/data_structures/../../header_files/data_structures/linked_list.h
global.o: src/global.c src/../header_files/global.h
helper.o: src/preprocessor/helper.c
macro.o: src/preprocessor/macro.c \
 src/preprocessor/../../header_files/preprocessor/macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h \
 src/preprocessor/../../header_files/data_structures/hashtable.h
macro_line_analizer.o: src/preprocessor/macro_line_analizer.c \
 src/preprocessor/../../header_files/data_structures/hashtable.h \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/preprocessor/preprocessor.h
preprocessor.o: src/preprocessor/preprocessor.c \
 src/preprocessor/../../header_files/global.h \
 src/preprocessor/../../header_files/preprocessor/macro.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/linked_list.h \
 src/preprocessor/../../header_files/preprocessor/helper.h \
 src/preprocessor/../../header_files/preprocessor/macro_line_analizer.h \
 src/preprocessor/../../header_files/preprocessor/../../header_files/data_structures/hashtable.h \
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

