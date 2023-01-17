.ORIG x3000

; take a keystroke and save it in R0
KEYBOARD_WAIT_LOOP
LDI R1, KBSR
BRzp KEYBOARD_WAIT_LOOP

; a keystroke is ready
LDI R0, KBDR
LD R1, ASCII_MASK
AND R0, R0, R1

; display the character in R0
DISPLAY_WAIT_LOOP
LDI R2, DSR
BRzp DISPLAY_WAIT_LOOP

; display is ready for our character
STI R0, DDR


HALT

KBSR .FILL xFE00
KBDR .FILL xFE02
DSR  .FILL xFE04
DDR  .FILL xFE06

ASCII_MASK .FILL x00FF

.END