.ORIG x3000

LEA R0, KBISR
STI R0, KBISR_PTR

LD R0, KBIE
STI R0, KBSR

LD R0, DOTCHAR
OUT
BRnzp #-3

KBISR
ADD R6, R6, #-3
STR R0, R6, #2
STR R1, R6, #1
LDI R0, KBDR
LDI R1, DSR
BRzp #-2
STI R0, DDR
LDR R0, R6, #2
LDR R1, R6, #1
ADD R6, R6, #3
RTI

DOTCHAR .STRINGZ "."
KBISR_PTR .FILL x0180
KBSR .FILL xFE00
KBDR .FILL xFE02
DSR .FILL xFE04
DDR .FILL xFE06
KBIE .FILL x4000

.END