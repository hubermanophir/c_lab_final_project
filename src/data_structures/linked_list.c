#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct LinkedList {
  Node *head;
  Node *tail;
} LinkedList;

LinkedList *init_list() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void free_list(LinkedList *list, void (*free_data)(void *)) {
  Node *current = list->head;
  Node *next;

  while (current != NULL) {
    next = current->next;
    free_data(current->data);
    free(current);
    current = next;
  }

  free(list);
}

void append_to_list_end(LinkedList *list, void *data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}