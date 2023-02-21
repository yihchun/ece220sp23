.ORIG x3000

LEA R6, STACK_BOT

; caller setup
ADD R6, R6, #-1
AND R0, R0, #0
ADD R0, R0, #3
STR R0, R6, #0
JSR FIB_R
HALT

; tmp <- R5, R6
; R5 save  R5+1
; R7 save  R5+2
; ret val  R5+3
; n        R5+4
; 
FIB_R
	; callee setup
	ADD R6, R6, #-4
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2
	
	; if (n==0) return 0
	LDR R0, R5, #4  ; load n
	BRz DO_RET_R0

	; if (n==1) return 1
	ADD R1, R0, #-1
	BRz DO_RET_R0

	; tmp = fib_r(n-1)
	; caller setup
	ADD R6, R6, #-1
	STR R1, R6, #0
	JSR FIB_R
	; caller teardown
	LDR R0, R6, #0   ; return value
	ADD R6, R6, #2
	STR R0, R5, #0   ; tmp = fib_r(n-1)

	; return tmp+fib_r(n-2);
	; caller setup
	LDR R0, R5, #4 ; load n
	ADD R0, R0, #-2 ; R0 <- n-2
	ADD R6, R6, #-1
	STR R0, R6, #0
	JSR FIB_R

	; caller teardown
	LDR R0, R6, #0 ; R0 <- fib(n-2)
	ADD R6, R6, #2
	LDR R1, R5, #0
	ADD R0, R0, R1 ; tmp + fib_r(n-2)
	
DO_RET_R0
	; callee teardown
	STR R0, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #3
	
	RET

FIB_R_R7_SAVE .FILL #0

STACK_TOP .BLKW #100
STACK_BOT .FILL #0

.END