.ORIG x3000

LD R1, TEST_A
LD R2, TEST_B

AND R3, R3, #0
LOOPTOP:
ADD R3, R3, R2
ADD R1, R1, #-1
BRnp LOOPTOP

HALT

TEST_A .FILL #0
TEST_B .FILL #1

.END