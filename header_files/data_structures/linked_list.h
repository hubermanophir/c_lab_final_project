#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct LinkedList {
  Node *head;
  Node *tail;
} LinkedList;

LinkedList *init_list();

/**
 * @brief Add data to the list tail tail
 *
 * @param list
 * @param data
 */
void add_to_list(LinkedList *list, void *data);

/**
 * @brief Free list from memory
 * 
 * @param list 
 * @param free_func 
 */
void free_list(LinkedList *list, void (*free_func)(void *));

#endif