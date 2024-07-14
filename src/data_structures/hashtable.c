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

  HashEntry *entry = (HashEntry *)malloc(sizeof(HashEntry));

  entry->key = key;
  entry->value = value;
  entry->next = hashtable->table[index];
  hashtable->table[index] = entry;
}

void *get_hashtable(Hashtable *hashtable, char *key) {
  int hashed_key = hash(key, hashtable->size);

  HashEntry *entry = hashtable->table[hashed_key];

  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      return entry->value;
    }

    entry = entry->next;
  }

  return NULL;
}

void free_hashtable(Hashtable *hashtable) {
  int i;
  for (i = 0; i < hashtable->size; i++) {
    HashEntry *entry = hashtable->table[i];

    while (entry) {
      HashEntry *next = entry->next;
      free(entry);
      entry = next;
    }
  }

  free(hashtable->table);
  free(hashtable);
}