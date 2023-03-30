.ORIG x3000

LEA R6, STACK_START
ADD R6, R6, #-1
JSR DELETE_ELEMENT
HALT

ADD R6, R6, #1 ; teardown
AND R0, R0, #0
ADD R0, R0, #4
STR R0, R6, #1
JSR INSERT_HEAD
HALT

; malloc function clobbers R0, R1, so maybe consider saving
; those if this becomes an issue
MALLOC
	LDR R0, R6, #0		; parameter
	LD R1, HEAP_PTR		; first free space
	ADD R0, R0, R1		; new first-free space
	ST R0, HEAP_PTR		; save first-free back to mem
	ADD R6, R6, #-1		; push newly allocated space
	STR R1, R6, #0
	RET			; return

INSERT_HEAD
	; callee setup
	ADD R6, R6, #-4
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2

	; tmp = malloc(sizeof(dllNode))
	; caller setup: push 3
	ADD R6, R6, #-1
	AND R0, R0, #0
	ADD R0, R0, #3
	STR R0, R6, #0
	
	JSR MALLOC

	; callee teardown
	LDR R2, R6, #0 ; return value
	ADD R6, R6, #2
	STR R2, R5, #0 ; tmp = malloc(3);

	; tmp->val = val
	LDR R0, R5, #0  ; tmp
	LDR R1, R5, #5  ; val
	STR R1, R0, #0

	; if (!*head)
	LDR R0, R5, #4
	LDR R0, R0, #0  ; *head
	BRnp LIST_NOT_EMPTY

	; tmp->prev = NULL
	LDR R0, R5, #0  ; tmp
	AND R1, R1, #0  ; NULL
	STR R1, R0, #2

	; tmp->next = NULL
	LDR R0, R5, #0  ; tmp
	AND R1, R1, #0  ; NULL
	STR R1, R0, #1

	; *head = tmp
	LDR R0, R5, #4  ; head
	LDR R1, R5, #0  ; tmp
	STR R1, R0, #0  ; *head = tmp

	BRnzp INSERT_HEAD_TEARDOWN

LIST_NOT_EMPTY
	; (*head)->prev = tmp
	LDR R0, R5, #4
	LDR R0, R0, #0  ; *head
	LDR R1, R5, #0  ; tmp
	STR R1, R0, #2

	; tmp->next = *head
	LDR R0, R5, #4
	LDR R0, R0, #0  ; *head
	LDR R1, R5, #0  ; tmp
	STR R0, R1, #1

	; tmp->prev = NULL
	LDR R0, R5, #0  ; tmp
	AND R1, R1, #0  ; NULL
	STR R1, R0, #2

	; *head = tmp
	LDR R0, R5, #4  ; head
	LDR R1, R5, #0  ; tmp
	STR R1, R0, #0  ; *head = tmp
	
INSERT_HEAD_TEARDOWN
	; callee teardown for INSERT_HEAD
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	RET

DELETE_ELEMENT
	; callee setup
	ADD R6, R6, #-4
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2

	; if (*head == victim)
	LDR R0, R5, #4
	LDR R0, R0, #0 ; *head
	LDR R1, R5, #5 ; victim
	NOT R1, R1
	ADD R1, R1, #1
	ADD R0, R0, R1
	BRnp NOT_FIRST_ELEMENT

	; *head = victim->next
	LDR R0, R5, #4
	LDR R1, R5, #5 ; victim
	LDR R1, R1, #1 ; victim->next
	STR R1, R0, #0

	; if (victim->next) victim->next->prev = NULL
	LDR R1, R5, #5 ; victim
	LDR R1, R1, #1
	BRz DELETE_ELEMENT_TEARDOWN
	AND R0, R0, #0
	STR R0, R1, #2
	BRnzp DELETE_ELEMENT_TEARDOWN
	
NOT_FIRST_ELEMENT
	; victim->prev->next = victim->next;
	LDR R1, R5, #5 ; victim
	LDR R2, R1, #1 ; R2 <- victim->next
	LDR R1, R1, #2 ; R1 <- victim->prev
	STR R2, R1, #1

	; if (victim->next) victim->next->prev = victim->prev;
	LDR R1, R5, #5 ; victim
	LDR R2, R1, #2
	LDR R1, R1, #1
	BRz DELETE_ELEMENT_TEARDOWN
	STR R2, R1, #2

DELETE_ELEMENT_TEARDOWN
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	RET
	

; tmp R5 #0
; R5 save R5 #1
; R7 save R5 #2
; return value R5 #3
; head R5 #4
; victim R5 #5

HEAD_POINTER .FILL A

A .FILL #2
  .FILL B
  .FILL #0
B .FILL #3
  .FILL C
  .FILL A
C .FILL #4
  .FILL #0
  .FILL B

STACK_END .BLKW #100
	  .FILL HEAD_POINTER
STACK_START .FILL A
HEAP_PTR .FILL HEAP_START
HEAP_START .BLKW #500

.END
	