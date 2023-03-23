#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList_Node {
  int data;
  struct LinkedList_Node *next;
} LLNode;

/* insert at the head of the linked list a new node with the value val */
void insert_head(LLNode **head, int val) {
  LLNode *tmp = malloc(sizeof(LLNode));
  tmp->data = val; /* 1 */
  tmp->next = *head; /* 2 */
  *head = tmp; /* 3 */
}

/* PRE: the input linked list is sorted
 * POST: we insert a new node with data "val" inserted in sorted (ascending)
 * order
 */
void insert_sorted(LLNode **head, int val) {
  LLNode *walk = *head;
  LLNode *tmp;
  if (!(*head) || val <= (*head)->data) {
    insert_head(head, val);
    return;
  }
  tmp = malloc(sizeof(LLNode));
  
  while (walk->next != NULL) {
    if (walk->next->data >= val)
      break;

    walk = walk->next;
  }
  /* insert the new element after walk (e.g., walk->next should be the new
   * element
   */
  tmp->data = val;
  tmp->next = walk->next;
  walk->next = tmp;
}

void print_linkedlist(const LLNode *head) {
  const LLNode *walk = head;
  /* for (walk = head; walk; walk = walk->next) */
  while (walk != NULL) {
    printf("%d ", walk->data);
    walk = walk->next;
  }
  
  printf("\n");
}

/* deletes the first node containing the value "victim" from the linked list
 * returns 1 if found and deleted
 * returns 0 otherwise
 */
int linkedlist_delete_first(LLNode **head, int victim) {
  /*
  LLNode *tmp;
  for (; *head; head = &((*head)->next)) {
    tmp = *head;
    if (tmp->data == victim) {
      *head = tmp->next;
      free(tmp);
      return 1;
    }
  }
  return 0;
  */
  LLNode *walk = *head;
  LLNode *tmp;
  if (walk->data == victim) {
    tmp = walk->next;
    free(*head);
    *head = tmp;
    return 1;    
  }
  while (walk != NULL) {
    if (walk->next && walk->next->data == victim) {
      tmp = walk->next;
      walk->next = walk->next->next;
      free(tmp);
      return 1;
    }
    walk = walk->next;
  }
  return 0;
}

int main() {
  LLNode *head = NULL;

  insert_sorted(&head, 6);
  insert_sorted(&head, 5);
  insert_sorted(&head, 8);
  insert_sorted(&head, 7);
  print_linkedlist(head);
  linkedlist_delete_first(&head, 6);
  print_linkedlist(head);
  linkedlist_delete_first(&head, 7);
  print_linkedlist(head);
  linkedlist_delete_first(&head, 5);
  print_linkedlist(head);


  return 0;
}
