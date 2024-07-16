#ifndef MACRO_H
#define MACRO_H

#include "../../header_files/data_structures/linked_list.h"
#include <stdio.h>
#include <string.h>

typedef struct Macro {
  char *name;
  LinkedList *lines;
} Macro;

/**
 * @brief Create a macro object
 * 
 * @return Macro* 
 */
Macro *create_macro();

/**
 * @brief Adds a macro name to the macro object
 * 
 * @param macro 
 * @param name 
 */
void add_macro_name(Macro *macro, char name[]);

/**
 * @brief Appending a new line to the macro
 * 
 * @param macro 
 * @param line 
 */
void append_macro_line(Macro *macro, char *line);

/**
 * @brief Free macro from memory
 * 
 * @param macro 
 */
void free_macro(Macro *macro);

/**
 * @brief Output macro code lines to an output file
 * 
 * @param macro 
 * @param output 
 */
void output_macro(Macro *macro, FILE *output);

#endif