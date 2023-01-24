.ORIG x3000

; TRAP x10: R1 * R2 -> R0
; save the trap service routine address to x10
;LEA R0, MULTIPLY_SERVICE_ROUTINE
;STI R0, HEX_TEN

; test harness
LD R1, OP1
LD R2, OP2
JSR FACTORIAL_FUNC
HALT

; compute R1 factorial -> R0
FACTORIAL_FUNC
	ST R7, FACT_SAVE_R7
	ADD R2, R1, #-1
	BRnz FACTORIAL_RETURN_ONE
MULTIPLE_MULTIPLY_LOOP
	JSR MULTIPLY_FUNC
	ADD R1, R0, #0
	ADD R2, R2, #-1
	BRp MULTIPLE_MULTIPLY_LOOP
	LD R7, FACT_SAVE_R7
	RET

FACTORIAL_RETURN_ONE
	AND R0, R0, #0
	ADD R0, R0, #1
	LD R7, FACT_SAVE_R7
	RET

FACT_SAVE_R7 .FILL #0
	
	

MULTIPLY_FUNC
	ST R1, MSR_R1
	AND R0, R0, #0	; R0 is accumulator
	ADD R1, R1, #0
	BRz DO_NOTHING
	LOOPTOP
	ADD R0, R0, R2  ; add R2 to R0 R1 times
	ADD R1, R1, #-1
	BRnp LOOPTOP
	LD R1, MSR_R1
	DO_NOTHING
	RET
			

OP1 .FILL #5
OP2 .FILL #6
MSR_R1 .FILL #0
MSR_R2 .FILL #0
HEX_TEN .FILL x10
.END