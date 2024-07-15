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

void *get_hashtable(Hashtable *hashtable, char *key);

void free_hashtable(Hashtable *hashtable);

void free_macro_hashtable(Hashtable *hashtable);

char **get_existing_macro_names(Hashtable *hashtable);

#endif