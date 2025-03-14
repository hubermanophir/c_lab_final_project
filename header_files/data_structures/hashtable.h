#ifndef HASHTABLE_H
#define HASHTABLE_H
typedef struct HashEntry {
  char *key;
  void *value;
  struct HashEntry *next;
} HashEntry;

typedef struct Hashtable {
  int size;
  HashEntry **table;
} Hashtable;

/**
 * @brief Create a hashtable object
 *
 * @param size
 * @return Hashtable
 */
Hashtable *create_hashtable(int size);

/**
 * @brief Puts a new value in the hashtable
 *
 * @param hashtable
 * @param key
 * @param value
 */
void put_hashtable(Hashtable *hashtable, char *key, void *value);

/**
 * @brief Free hashtable and its values from memory
 *
 * @param hashtable
 * @param free_value
 */
void free_hashtable(Hashtable *hashtable, void (*free_value)(void *));

/*Macro Hashtable methods*/
/**
 * @brief Update **existing_names to include the existing macro names
 *
 * @param hashtable
 * @param existing_names
 * @return length of existing names array
 */
int get_existing_macro_names(Hashtable *hashtable, char ***existing_names);

/**
 * @brief Get the macro from hashtable by name
 *
 * @param hashtable
 * @param key
 * @return void*
 */
void *get_by_name_field_hashtable(Hashtable *hashtable, char *key);

/*End of Macro Hashtable methods*/
/**
 * @brief This function is updating the existing_values array to be 
 all the pointers to the pointers in the hashtable
 * 
 * @param hashtable 
 * @param existing_values 
 * @return int the size of the existing_values array
 */
int get_existing_values(Hashtable *hashtable, void ***existing_values);

#endif