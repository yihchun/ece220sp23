#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList_Node {
  int data;
  struct LinkedList_Node *next;
} LLNode;

typedef struct {
  LLNode *head;
  LLNode *tail;
} LLQueue;

/* Delete the last-in element of list. If list is empty, return -1 */
int dequeue(LLQueue *list) {
  LLNode *tmp;
  int ret;
  /* check for empty list */
  if (!list->head)
    return -1;
  tmp = list->head->next;
  ret = list->head->data;
  free(list->head);
  list->head = tmp;
  if (tmp == NULL)
    list->tail = NULL;
  return ret;
}

void insert_head(LLQueue *list, int val) {
  LLNode *tmp = malloc(sizeof(LLNode));
  
  tmp->data = val;
  tmp->next = list->head;
  list->head = tmp;
  if (list->tail == NULL)
    list->tail = tmp;
}

void enqueue(LLQueue *list, int val) {
  LLNode *tmp;
  if (list->head == NULL)
    return insert_head(list, val);

  tmp = malloc(sizeof(LLNode));

  list->tail->next = tmp;
  tmp->data = val;
  tmp->next = NULL;
  list->tail = tmp;
}

void print_queue(LLQueue list) {
  const LLNode *walk = list.head;
  /* for (walk = head; walk; walk = walk->next) */
  while (walk != NULL) {
    printf("%d ", walk->data);
    walk = walk->next;
  }
  
  printf("\n");
}

int main() {
  LLQueue list = {NULL, NULL};
  enqueue(&list, 5);
  enqueue(&list, 6);
  enqueue(&list, 7);
  enqueue(&list, 8);
  printf("%d\n", dequeue(&list));
  printf("%d\n", dequeue(&list));
  enqueue(&list, 9);
  printf("%d\n", dequeue(&list));
  printf("%d\n", dequeue(&list));
  printf("%d\n", dequeue(&list));
  printf("%d\n", dequeue(&list));
  return 0;
}
