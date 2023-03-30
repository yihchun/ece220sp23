#include <stdio.h>
#include <stdlib.h>

typedef struct dllNode {
  int val;
  struct dllNode *next;
  struct dllNode *prev;
} dllNode;

void insertHead(dllNode **head, int val) {
  dllNode *tmp = malloc(sizeof(dllNode));
  tmp->val = val;
  if (!*head) {
    tmp->next = tmp->prev = NULL;
    *head = tmp;
  } else {
    (*head)->prev = tmp;
    tmp->next = *head;
    tmp->prev = NULL;
    *head = tmp;
  }
  /*
    tmp->val = val;
    tmp->prev = NULL;
    if (*head) {
      (*head)->prev = tmp;
    }
    tmp->next = *head;
    *head = tmp;
  */
}

void deleteElement(dllNode **head, dllNode *victim) {
  dllNode *tmp;
  if (*head == victim) { /* alt. victim->prev == NULL */
    *head = victim->next;
    if (victim->next)
      victim->next->prev = NULL; /* (*head)->prev = NULL */
    free(victim);
  } else {
    victim->prev->next = victim->next;
    if (victim->next)
      victim->next->prev = victim->prev;
    free(victim);
  }
}

dllNode *find(dllNode *head, int val) {
  dllNode *walk;
  for (walk = head; walk != NULL; walk = walk->next)
    if (walk->val == val)
      return walk;
  
  return walk;
}

int main() {
  dllNode *head = NULL;
  dllNode *tmp;
  insertHead(&head, 10);
  insertHead(&head, 5);
  insertHead(&head, 2);
  tmp = find(head, 2);
  deleteElement(&head, tmp);
  printf("%d %p %p %p\n", head->val, head, head->next, head->next->prev);
  return 0;
}

