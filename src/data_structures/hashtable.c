#include "../../header_files/preprocessor/macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashEntry {
  char *key;
  void *value;
  struct HashEntry *next;
} HashEntry;

typedef struct Hashtable {
  int size;
  HashEntry **table;
} Hashtable;

int hash(char *key, int size) {
  int hash = 0;
  int i;

  for (i = 0; key[i] != '\0'; i++) {
    hash += key[i];
  }

  return hash % size;
}

Hashtable *create_hashtable(int size) {
  int i;
  Hashtable *hashtable = (Hashtable *)malloc(sizeof(Hashtable));
  hashtable->size = size;
  hashtable->table = (HashEntry **)malloc(sizeof(HashEntry *) * size);
  if (hashtable->table == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  for (i = 0; i < size; i++) {
    hashtable->table[i] = NULL;
  }

  return hashtable;
}

void put_hashtable(Hashtable *hashtable, char *key, void *value) {
  int index = hash(key, hashtable->size);
  HashEntry *entry;
  HashEntry *current = hashtable->table[index];
  if (current == NULL) {
    entry = (HashEntry *)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    hashtable->table[index] = entry;
  } else {
    while (current->next) {
      current = current->next;
    }
    entry = (HashEntry *)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    current->next = entry;
  }
}

void free_hashtable(Hashtable *hashtable, void (*free_value)(void *)) {
  int i;
  for (i = 0; i < hashtable->size; i++) {
    HashEntry *entry = hashtable->table[i];

    while (entry) {
      HashEntry *next = entry->next;
      free_value(entry->value);
      free(entry); 
      entry = next;
    }
  }

  free(hashtable->table);
  free(hashtable);
}

/*Macro Hashtable methods*/

int get_existing_macro_names(Hashtable *hashtable, char ***existing_names) {
  int capacity = hashtable->size;
  int count = 0, i;

  *existing_names = (char **)malloc(sizeof(char *) * capacity);

  for (i = 0; i < hashtable->size; i++) {
    HashEntry *entry = hashtable->table[i];

    while (entry) {
      if (count == capacity) {
        capacity *= 2;
        *existing_names =
            (char **)realloc(*existing_names, sizeof(char *) * capacity);
      }
      (*existing_names)[count] = ((Macro *)(entry->value))->name;
      count++;
      entry = entry->next;
    }
  }

  return count;
}

void *get_macro_hashtable(Hashtable *hashtable, char *key) {
  int hashed_key = hash(key, hashtable->size);
  HashEntry *entry = hashtable->table[hashed_key];

  while (entry) {
    if (strcmp(((Macro *)(entry->value))->name, key) == 0) {
      return entry->value;
    }

    entry = entry->next;
  }

  return NULL;
}

/*End of Macro Hashtable methods*/