CC			= gcc
CFLAGS		= -ansi -pedantic -Wall
PROG_NAME 	= assembler
BUILD_DIR	= build
OBJ_DIR		= $(BUILD_DIR)/obj
BIN_DIR		= $(BUILD_DIR)/bin
ZIP_NAME	= mmn22.zip

ifdef DEBUG
CFLAGS += -g
endif
 
.PHONY: clean build_env all
 
all: build_env $(PROG_NAME) 
 
$(PROG_NAME): assembler.o preprocessor.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/$@
 
assembler.o: src/assembler.c src/./preprocessor/preprocessor.h
preprocessor.o: src/preprocessor/preprocessor.c

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
