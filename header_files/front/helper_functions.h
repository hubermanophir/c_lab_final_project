#ifndef FRONT_HELPER_FUNCTIONS_H
#define FRONT_HELPER_FUNCTIONS_H

/**
 * @brief Converts a string to an integer Supports negative numbers
 * 
 * @param str 
 * @return int 
 */
int convert_number_str_to_int(char *str);

/**
 * @brief Checks if a string is a number and if it is it converts it
 *
 * @param str
 * @return int
 */
int is_number(char *str);

/**
 * @brief Checks if a register number is between 0-7
 *
 * @param str
 * @return int
 */
int is_valid_reg_num(char *str);

/**
 * @brief simple check if a string is a comma
 *
 * @param str
 * @return int
 */
int is_comma_str(char *str);

#endif