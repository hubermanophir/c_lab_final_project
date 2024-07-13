typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct LinkedList {
  Node *head;
  Node *tail;
} LinkedList;

void init_list(LinkedList *list);

void add_to_list(LinkedList *list, void *data);

void free_list(LinkedList *list);