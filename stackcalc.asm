.ORIG x3000

; 3 4 + 5 x
; 3: push 3
; 4: push 4
; +: pop two values (3,4), add them, and push the result (7)
; 5: push 5
; -: pop two values (7,5), subtract them, and push the result (2)

LEA R1, EVAL_STRING
LEA R6, BOT_OF_STACK_PLUS1
	
LOOPTOP
	LDR R0, R1, #0
	BRz END_OF_STRING
	; check if R0 is a digit
	ADD R0, R0, #-16
	ADD R0, R0, #-16
	ADD R0, R0, #-16 ; subtract x30
	BRn NOT_A_DIGIT  ; if our char < x30, not a digit
	ADD R2, R0, #-9
	BRp NOT_A_DIGIT  ; if our char > x39, not a digit
	JSR PUSH         ; push the digit
	ADD R5, R5, #0   ; check for overflow
	BRp OVERFLOW_STACK
	ADD R1, R1, #1   ; move to next character
	BRnzp LOOPTOP
NOT_A_DIGIT
	LDR R0, R1, #0   ; reload the current character
	NOT R0, R0  	 ; negate the current character to check against operators
	ADD R0, R0, #1
	LEA R2, OPS_STRING
	LDR R3, R2, #0
	ADD R3, R3, R0    ; will be zero if the operation is +
	BRz STACK_ADD
	LDR R3, R2, #1
	ADD R3, R3, R0    ; will be zero if the operation is +
	BRz STACK_SUBTRACT
	; handle other characters
	; e.g. print error, increment R1, BRnzp LOOPTOP

STACK_ADD		  ; handle the + operator
	JSR POP           ; pop the second operand
	; TODO: check R5
	ADD R4, R0, #0    ; move second operand to R4
	JSR POP           ; pop the first operand
	; TODO: check R5
	ADD R0, R0, R4    ; add operands together
	JSR PUSH    	  ; push the sum to the stack
	ADD R1, R1, #1    ; go to next character
	BRnzp LOOPTOP

END_OF_STRING
	HALT

OVERFLOW_STACK
	LEA R0, OVERFLOW_MESSAGE
	PUTS
	HALT

OVERFLOW_MESSAGE .STRINGZ "uggggh I'm sooo full"
	
EVAL_STRING .STRINGZ "34+"
OPS_STRING .STRINGZ "+-*/"

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
