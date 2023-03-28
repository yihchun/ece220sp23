#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList_Node {
  int data;
  struct LinkedList_Node *next;
} LLNode;

typedef LLNode *LLStack;

/* insert at the head of the linked list a new node with the value val */
void LLStack_push(LLStack *head, int val) {
  LLNode *tmp = malloc(sizeof(LLNode));
  tmp->data = val; /* 1 */
  tmp->next = *head; /* 2 */
  *head = tmp; /* 3 */
}

void print_stack(const LLStack head) {
  const LLNode *walk = head;
  /* for (walk = head; walk; walk = walk->next) */
  while (walk != NULL) {
    printf("%d ", walk->data);
    walk = walk->next;
  }
  
  printf("\n");
}

/* return the top of the stack. Return -1 if the stack is empty.
 */
int LLStack_pop(LLStack *head) {
  LLNode *walk = *head;
  LLNode *tmp;
  int var;

  if (*head == NULL)
    return -1;

  var = walk->data;
  tmp = walk->next;
  free(*head);
  *head = tmp;
  return var;
}

int main() {
  LLStack stack = NULL;

  LLStack_push(&stack, 6);
  LLStack_push(&stack, 5);
  LLStack_push(&stack, 7);
  LLStack_push(&stack, 4);
  print_stack(stack);
  printf("%d\n", LLStack_pop(&stack));
  printf("%d\n", LLStack_pop(&stack));
  printf("%d\n", LLStack_pop(&stack));
  printf("%d\n", LLStack_pop(&stack));

  return 0;
}
