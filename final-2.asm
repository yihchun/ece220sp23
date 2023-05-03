.ORIG x3000

MAIN
	; callee setup: 3 local variables
	ADD R6, R6, #-6
	STR R7, R6, #4
	STR R5, R6, #3
	ADD R5, R6, #2

	; a = 10
	AND R2, R2, #0
	ADD R2, R2, #10
	STR R2, R5, #0

	; b = 20
	ADD R2, R2, #10
	STR R2, R5, #-1
	
	; c = a+b
	LDR R3, R5, #0
	ADD R2, R2, R3
	STR R2, R5, #-2

	; printf("c = %d\n", c);
	; this is too hard for us...

	; return 0
	AND R2, R2, #0
	STR R2, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	ADD R6, R6, #5
	RET


.END