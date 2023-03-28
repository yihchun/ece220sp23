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

void delete_head(LinkedList *list) {
  LLNode *tmp;
  /* check for empty list */
  if (!list->head)
    return;
  tmp = list->head->next;
  free(list->head);
  list->head = tmp;
  if (tmp == NULL)
    list->tail = NULL;
}

/* delete the first instance of victim in list */
int delete_first(LinkedList *list, int victim) {
  LLNode *walk;
  LLNode *tmp;
  /* check for empty list */
  if (list->head == NULL)
    return 0;
  /* check for the case where we delete the first element */
  if (list->head->data == victim) {
    delete_head(list);
    return 1;
  }
  walk = list->head;
  while (walk->next != NULL) {
    if (walk->next->data == victim) {
      tmp = walk->next;
      if (walk->next->next == NULL)
	list->tail = walk;
      walk->next = walk->next->next; /* in prof. hu's opinion should be tmp->next */
      free(tmp);
      /* my approach:
	 if (list->tail == tmp)
	   list->tail = walk;
      */
      return 1;
    }
    walk = walk->next;
  }
  return 0;
}

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
  delete_head(&list);
  print_linkedlist(list);
  delete_first(&list, 10);
  insert_tail(&list, 11);
  print_linkedlist(list);
  return 0;
}
