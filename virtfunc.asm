.ORIG x3000

; x->identify()
LD R1, X       ; R1 <- &b
LDR R2, R1, #0 ; R2 <- vft
LDR R3, R2, #0 ; R3 <- applicable identify() function
JSRR R3

; x = &z
LEA R1, Z
ST R1, X

; x->identify()
LD R1, X       ; R1 <- &z
LDR R2, R1, #0 ; R2 <- vft
LDR R3, R2, #0 ; R3 <- applicable identify() function
JSRR R3

HALT

FOO_IDENTIFY
	LEA R0, FOOSTR
	ST R7, R7_SAVE
	PUTS
	LD R7, R7_SAVE
	RET

BAR_IDENTIFY
	LEA R0, BARSTR
	ST R7, R7_SAVE
	PUTS
	LD R7, R7_SAVE
	RET

BAZ_IDENTIFY
	LEA R0, BAZSTR
	ST R7, R7_SAVE
	PUTS
	LD R7, R7_SAVE
	RET

FOO_VFT .FILL FOO_IDENTIFY
BAR_VFT .FILL BAR_IDENTIFY
BAZ_VFT .FILL BAZ_IDENTIFY

X .FILL B        ; x = &b;
B .FILL BAR_VFT
  .FILL #0       ; b.z
Z .FILL BAZ_VFT
  .FILL #0       ; z.z


R7_SAVE .FILL #0
FOOSTR .STRINGZ "I am a Foo\n"
BARSTR .STRINGZ "I am a Bar\n"
BAZSTR .STRINGZ "I am a Baz\n"
.END