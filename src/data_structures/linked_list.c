#include "../../header_files/data_structures/data_structures.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(LinkedList *list) {
  list->head = NULL;
  list->tail = NULL;
}

void add_to_list(LinkedList *list, void *data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = list->tail;

  if (list->tail) {
    list->tail->next = new_node;
  }

  list->tail = new_node;

  if (!list->head) {
    list->head = new_node;
  }
}

void free_list(LinkedList *list) {
  Node *current = list->head;
  Node *next;

  while (current) {
    next = current->next;
    free(current);
    current = next;
  }

  list->head = NULL;
  list->tail = NULL;
}