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

LinkedList * init_list();

void add_to_list(LinkedList *list, void *data);

void free_list(LinkedList *list);

void print_list(LinkedList *list);

#endif