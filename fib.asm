.ORIG x3000

; R0 -- n
FIB_R
	ST R7, FIB_R_R7_SAVE
	; if (n == 0) return 0;
	ADD R0, R0, #0
	BRz DO_RET_R0
	ADD R0, R0, #-1
	BRz DO_RET_R0_PLUS_ONE
	ADD R1, R0, #-1 ; save n-2
	JSR FIB_R  ; call fib(n-1)
	ADD R2, R0, #0 ; R2 now holds fib(n-1)
	ADD R0, R1, #0
	JSR FIB_R ; call fib(n-2)?
	ADD R0, R2, R0
	LD R7, FIB_R_R7_SAVE
	RET

DO_RET_R0_PLUS_ONE
	ADD R0, R0, #1
DO_RET_R0
	RET

FIB_R_R7_SAVE .FILL #0

.END