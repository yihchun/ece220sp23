.ORIG x3000

; two main operations
; PUSH - inserts an item into the stack (cannot specify an order)
;        [pushes the item on top of the stack]
; POP - removes (and returns) the most recently inserted item (that has
;       not yet been popped) [removes and returns the top of the stack]
; possible other operations
; isEmpty - returns true if stack is empty, false otherwise
; isFull - returns true if stack is full, false otherwise
; peek - looks at the most recently inserted (but not popped) item of
; the stack without removing it
; terminology
;   top of stack - the next item to pop
;   capacity - the maximum number of items in the stack

; stack pointer init
LEA R6, BOT_OF_STACK_PLUS1 ; initialize the stack pointer

; Register initialization
; R4 address of the character currently being analyzed
; R2 -'('
; R3 -'['
LEA R4, TEST_STRING
LD R2, OPENPAREN
NOT R2, R2
ADD R2, R2, #1
LD R3, OPENBRACKET
NOT R3, R3
ADD R3, R3, #1

; R1 current character
; R0 temporary register
LOOPTOP
	LDR R1, R4, #0    ; load the current character
	BRz END_OF_STRING ; if NUL, then at end of string
	ADD R0, R1, R2    ; computes char-'('
	BRz HANDLE_OPEN   ; if zero, then open paren
	ADD R0, R0, #-1   ; compute char-')'
	BRz HANDLE_CLOSED_PAREN ; if zero, then closed paren
	ADD R0, R1, R3    ; compute char-'['
	BRz HANDLE_OPEN  ; if zero, then open bracket
	ADD R0, R0, #-2  ; compute char-']' (']' - '[' == 2)
	BRz HANDLE_CLOSED_BRACKET ; if zero, then closed bracket
	ADD R4, R4, #1   ; ignore the non-parenthetical character
	BRnzp LOOPTOP
	
HANDLE_OPEN
	ADD R0, R1, #0   ; push the current char (now in R1, needs to be in R0)
	                 ; R0 <- R1+0 == R1
	JSR PUSH	 ; push R0 onto the stack
	ADD R5, R5, #0   ; check R5 to make sure we didn't overflow
	BRp STRING_TOO_LONG
	ADD R4, R4, #1   ; move to next character
	BRnzp LOOPTOP

HANDLE_CLOSED_PAREN
	JSR POP		 ; pop and check that we match '('
	ADD R5, R5, #0	 ; set condition code based on R5 (success/failure)
	BRp OOPS_FAILED ; POP on empty stack
	ADD R0, R0, R2   ; compute popped value - '('
	BRnp OOPS_FAILED ; non-zero if '(' is not matched
	ADD R4, R4, #1   ; move to next character
	BRnzp LOOPTOP

HANDLE_CLOSED_BRACKET
	JSR POP		 ; pop and check that we match '['
	ADD R5, R5, #0	 ; set condition code based on R5 (success/failure)
	BRp OOPS_FAILED  ; POP on empty stack
	ADD R0, R0, R3   ; compute popped value - '[' (0 if popped a '[')
	BRnp OOPS_FAILED ; non-zero if '[' is not matched
	ADD R4, R4, #1   ; move to next character
	BRnzp LOOPTOP

END_OF_STRING
	JSR POP		 ; check if anything is still on the stack
	ADD R5, R5, #0   ; if pop was successful, something is on the stack
	BRz OOPS_FAILED  ; ...so fail
	LEA R0, SUCCESS_STRING ; indicate that parens match
	BRnzp PUTS_HALT

OOPS_FAILED
	LEA R0, FAILURE_STRING ; complain
	BRnzp PUTS_HALT

STRING_TOO_LONG
	LEA R0, OVERFULL_STACK
PUTS_HALT
	PUTS
	HALT

OPENPAREN .STRINGZ "("
OPENBRACKET .STRINGZ "["
TEST_STRING .STRINGZ "[([])([()][])]()"
SUCCESS_STRING .STRINGZ "Your parentheses match"
FAILURE_STRING .STRINGZ "Your parentheses don't match"
OVERFULL_STACK .STRINGZ "Our stack is too small to check your string"

; PUSH - push R0 to the top of the stack
; R5 will be 0 if successful, and 1 otherwise
PUSH
	; is R6 == TOP_OF_STACK?
	LEA R5, TOP_OF_STACK
	NOT R5, R5
	ADD R5, R5, #1 ; R5 <- -TOP_OF_STACK
	ADD R5, R6, R5 ; R5 <- R6-TOP_OF_STACK
	BRnz CANNOT_PUSH
	
	ADD R6, R6, #-1
	STR R0, R6, #0
	AND R5, R5, #0
	BRnzp RET_FROM_PUSH

CANNOT_PUSH
	AND R5, R5, #0
	ADD R5, R5, #1

RET_FROM_PUSH
	RET

; POP - pops the top element from the stack into R0
; R5 will be 0 if successful, and 1 otherwise

POP
	; is R6 == BOT_OF_STACK_PLUS1
	LEA R5, BOT_OF_STACK_PLUS1
	NOT R5, R5
	ADD R5, R5, #1 ; R5 <- -BOT_OF_STACK_PLUS1
	ADD R5, R6, R5 ; R5 <- R6-BOT_OF_STACK_PLUS1
	               ; now R5 = -# of items in stack
	BRzp CANNOT_POP

	LDR R0, R6, #0 ; top of stack
	ADD R6, R6, #1 ; remove one item from stack
	AND R5, R5, #0 ; clear R5 to indicate success
	BRnzp RET_FROM_POP

CANNOT_POP
	AND R5, R5, #0
	ADD R5, R5, #1 ; R5 <- 1 to indicate failure

RET_FROM_POP
	RET ; return to the caller


; X has matched parenthesis if X is formed using the following rules:
; X <- empty string
; X <- [X]
; X <- (X)
; X <- XX

TOP_OF_STACK       .BLKW #100
BOT_OF_STACK_PLUS1 .FILL #0


.END

