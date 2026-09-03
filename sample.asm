LDAA #7 ; A = 7
TAB     ; B = A

LDAA #3 ; A = 3;
ABA     ; A = A + B + Cin
SAL     ; A << 1

ABA     ; A = A + B + Cin
SAR     ; A >> 1
JMP 2   ; PC = 2

LDAA #$C ; This code will never run
ABA