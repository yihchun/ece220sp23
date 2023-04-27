.ORIG x3000

LEA R6, STACK_START
JSR DELETE_NODE
HALT

DELETE_NODE
	; callee setup
	ADD R6, R6, #-5
	STR R5, R6, #2
	STR R7, R6, #3
	ADD R5, R6, #1

	; cur = list->head
	LDR R1, R5, #4
	LDR R2, R1, #0
	STR R2, R5, #0

	; if (!cur) return;
	BRz DELETE_NODE_TEARDOWN

	; if (cur->data == data)
	LDR R0, R5, #5 ; data
	LDR R2, R5, #0 ; cur
	LDR R3, R2, #0 ; cur->data
	NOT R0, R0
	ADD R0, R0, #1 ; -data
	ADD R3, R0, R3 ; cur->data-data
	BRnp LOOPTOP
	
	; if (list->head == list->tail)
	LDR R0, R5, #4
	LDR R1, R0, #0
	LDR R2, R0, #1
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R1, R2
	BRnp #1
	STR R1, R0, #1 ; list->tail = NULL
	; list->head = cur->next
	LDR R0, R5, #4 ; list
	LDR R1, R5, #0 ; cur
	LDR R2, R1, #1 ; cur->next
	STR R2, R0, #0 ; list->head = cur->next
	; free(cur)
	BRnzp DELETE_NODE_TEARDOWN

LOOPTOP
	; while (cur->next)
	LDR R1, R5, #0 ; cur
	LDR R2, R1, #1 ; cur->next
	BRz DELETE_NODE_TEARDOWN
	; if (cur->next->data == data)
	LDR R3, R2, #0 ; cur->next->data
	LDR R0, R5, #5 ; data
	NOT R0, R0
	ADD R0, R0, #1 ; -data
	ADD R0, R0, R3 ; cur->next->data
	BRnp LOOPBOT
	; victim = cur->next
	STR R2, R5, #-1
	; cur->next = victim->next
	LDR R4, R2, #1 ; victim->next
	LDR R0, R5, #0
	STR R4, R0, #1
	; free(victim)
	; if (cur->next == NULL)
	ADD R4, R4, #0
	BRnp #3
	; in three lines, list->tail = cur
	LDR R0, R5, #4 ; list
	LDR R1, R5, #0 ; cur
	STR R1, R0, #1
	BRnzp DELETE_NODE_TEARDOWN

LOOPBOT
	; cur = cur->next
	LDR R1, R5, #0 ; cur
	LDR R2, R1, #1
	STR R2, R5, #0
	BRnzp LOOPTOP

DELETE_NODE_TEARDOWN
	; callee teardown
	ADD R6, R6, #4
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET

; victim   <- R6
; cur      <- R5
; r5 save
; r7 save
; ret val
; list     +4
; data     +5

A .FILL #1
  .FILL #0
B .FILL #2
  .FILL C
C .FILL #3
  .FILL #0
LIST .FILL A
     .FILL A

STACK_END .BLKW #30
STACK_START .FILL LIST
.FILL #1



.END