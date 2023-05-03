#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int val;
  struct node *next;
} node;

node *reverse_linked_list(node *old_head) {
  /* returns the new head */
  node *a, *b, *c;

  if (!old_head) return NULL;
  if (!old_head->next) return old_head;
  
  c = old_head;
  b = c->next;
  old_head->next = NULL;
  while (b->next) {
    printf("Working from %p [%d]\n", c, c->val);
    printf("Next is %p [%d]\n", b, b->val);
    printf("Next Next is %p\n", a);
    a = b->next;
    b->next = c;
    c = b;
    b = a;
  }
  b->next = c;
  printf("returning %p\n", b);
  return b;
}

void insert_head(node **head, int x) {
  node *tmp = malloc(sizeof(node));
  tmp->val = x;
  tmp->next = *head;
  *head = tmp;
}

void traverse(const node *head) {
  while (head) {
    printf("%d\n", head->val);
    head = head->next;
  }
}

int main() {
  node *head = NULL;
  insert_head(&head, 5);
  insert_head(&head, 4);
  insert_head(&head, 3);
  insert_head(&head, 2);
  insert_head(&head, 1);
  traverse(head);
  traverse(reverse_linked_list(head));
  return 0;
}
