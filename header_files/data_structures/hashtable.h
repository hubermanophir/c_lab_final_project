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

Hashtable *create_hashtable(int size);

void put_hashtable(Hashtable *hashtable, char *key, void *value);

void free_hashtable(Hashtable *hashtable, void (*free_value)(void *));
/*Macro Hashtable methods*/

int get_existing_macro_names(Hashtable *hashtable, char ***existing_names);

void *get_macro_hashtable(Hashtable *hashtable, char *key);

/*End of Macro Hashtable methods*/

#endif