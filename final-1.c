#include <stdio.h>

typedef struct node {
  int data;
  struct node *next;
} llnode;

typedef struct linked_list {
  struct node *head;
  struct node *tail;
} linked_list;

/* Delete a node from the linked list */
void delete_node(linked_list *list, int data) {
  llnode *cur = list->head;
  llnode *victim;
  if (!cur) return;
  if (cur->data == data) {
    if (list->head == list->tail) {
      list->tail = NULL;
    }
    list->head = cur->next;
    free(cur);
    return;
  }
  while (cur->next) {
    if (cur->next->data == data) {
      victim = cur->next;
      cur->next = victim->next;
      free(victim);
      if (cur->next == NULL)
	list->tail = cur;
      return;
    }
    cur = cur->next;
  }
}
  
  
