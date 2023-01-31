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

TRAIN_REORDER
; Algorithm:
; 1. check if out car is equal to the in car, if so, over
; 2. check if out car is equal to the top of stack, if so, pop
; 3. push the input car
; Register allocation
; R1 point to the current car input order
; R2 points to the current car in the output order
; R3 is negative of the label of the next output car
LEA R1, INPUT_ORDER
LEA R2, OUTPUT_ORDER

TRLOOPTOP
	LDR R3, R2, #0
	BRz SUCCESS     ; we've output every requested car,
	    		; sounds like a good day at the office
	NOT R3, R3
	ADD R3, R3, #1
	LDR R4, R1, #0  ; current input car
	ADD R5, R4, R3  ; current in - next out
	BRz DO_OVER
	JSR POP
	ADD R5, R5, #0  ; set condition code based on success/failure
	BRp DO_PUSH     ; nothing on the stack, so POP is not possible
	ADD R5, R0, R3  ; compute top-of-stack - next out
	BRz DO_POP
	JSR PUSH        ; repush the PEEK'ed car to the stack
DO_PUSH
	LDR R0, R1, #0  ; the current input car
	BRz NO_SOLUTION ; don't allow pushing of cars that don't exist
	JSR PUSH        ; push it on the stack
	ADD R5, R5, #0
	BRp OVERFULL_SPUR
	LD R0, PUSH_LABEL
	OUT
	ADD R1, R1, #1  ; move to next input car since we pushed the current one
	BRnzp TRLOOPTOP

DO_OVER
	LD R0, OVER_LABEL ; tell the user we're sending a car over
	OUT
	ADD R1, R1, #1    ; move on to the next input car
	ADD R2, R2, #1    ; move on to the next output car
	BRnzp TRLOOPTOP

DO_POP
	LD R0, POP_LABEL
	OUT
	ADD R2, R2, #1    ; move to the next output car
	BRnzp TRLOOPTOP

NO_SOLUTION
	LEA R0, NO_SOLUTION_STRING
	PUTS
SUCCESS
	HALT

OVERFULL_SPUR
	LEA R0, SPUR_IS_FULL
	PUTS
	HALT

SPUR_IS_FULL .STRINGZ "The spur has insufficient space to evaluate a solution."
NO_SOLUTION_STRING .STRINGZ "There is no solution."
OVER_LABEL .STRINGZ "V"
PUSH_LABEL .STRINGZ "U"
POP_LABEL  .STRINGZ "O"

INPUT_ORDER .STRINGZ "ABCDEF"
OUTPUT_ORDER .STRINGZ "FABCDE"


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

PARENTHESIS_MATCH
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

.END

