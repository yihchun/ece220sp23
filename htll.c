#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList_Node {
  int data;
  struct LinkedList_Node *next;
} LLNode;

typedef struct {
  LLNode *head;
  LLNode *tail;
} LinkedList;

void insert_head(LinkedList *list, int val) {
  LLNode *tmp = malloc(sizeof(LLNode));
  
  tmp->data = val;
  tmp->next = list->head;
  list->head = tmp;
  if (list->tail == NULL)
    list->tail = tmp;
}

void insert_tail(LinkedList *list, int val) {
  LLNode *tmp;
  if (list->head == NULL)
    return insert_head(list, val);

  tmp = malloc(sizeof(LLNode));

  list->tail->next = tmp;
  tmp->data = val;
  tmp->next = NULL;
  list->tail = tmp;
}

void print_linkedlist(LinkedList list) {
  const LLNode *walk = list.head;
  /* for (walk = head; walk; walk = walk->next) */
  while (walk != NULL) {
    printf("%d ", walk->data);
    walk = walk->next;
  }
  
  printf("\n");
}

int main() {
  LinkedList list = {NULL, NULL};
  insert_head(&list, 5);
  insert_tail(&list, 6);
  insert_head(&list, 7);
  insert_tail(&list, 8);
  insert_head(&list, 9);
  insert_tail(&list, 10);
  print_linkedlist(list);
  return 0;
}
