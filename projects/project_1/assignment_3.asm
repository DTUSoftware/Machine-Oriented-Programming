        .ORIG x3000
        LEA     R1, isPrime
        JMP     R1
        TRAP    x25
;
; function to check if a given number in
; R0 is a prime number
;
isPrime ;save registers
        ADD     R6, R6, #-1 ; store R1 (modulo argument)
        STR     R1, R6, #0  ; onto the stack
        ADD     R6, R6, #-1 ; store R2 (storage)
        STR     R2, R6, #0  ; onto the stack
        ADD     R6, R6, #-1 ; store R3 (jump)
        STR     R3, R6, #0  ; onto the stack
;
; check if R0 is 2
        ADD     R0, R0, #-2 ; check if R0
        BRz     YES         ; is equal to 2
        ADD     R0, R0, #2  ; restore R0
;
; check mod-2 of R0
        LDR     R2, R0, #0  ; store R0 into R2 (modulo will change it)
        LD      R1, #2      ; set second argument to 2
        LEA     R3, MOD
        JMP     R3
        ADD     R0, R0, #0
        BRnp    NO
        LDR     R0, R2, #0  ; restore R0 from R2
;
; check if prime number
        LD      R1, #0      ; initialize R1 to 0
; sqrt check
checkP  LDR     R2, R0, #0  ; temp storage for R0
        LDR     R0, R1, #0
        LEA     R3, MUL
        JMP     R3          ; check if sqrt(R1) < R0
        NOT     R0, R0      ; by multiplying it
        ADD     R0, R0, #1  ; by itself, and adding it
        ADD     R0, R2, R0  ; to R0 (temp in R2), and checking if negative
        BRn     YES
        LDR     R0, R2, #0  ; restore R0 from R2
; mod check
        ADD     R1, R1, #3
        LEA     R3, MOD
        JMP     R3
        ADD     R0, R0, #0
        BRz     NO
        ADD     R1, R1, #-1 ; subtract 3 and add 2
        BRnzp   checkP
;
;
NO      AND     R0, R0, #0
        BRnzp   RESTORE
;
YES     LD      R0, #1
;
RESTORE LDR     R1, R6, #0  ; restore R1
        ADD     R6, R6, #1  ; from the stack
        LDR     R2, R6, #0  ; restore R2
        ADD     R6, R6, #1  ; from the stack
        LDR     R3, R6, #0  ; restore R3
        ADD     R6, R6, #1  ; from the stack
        RET
;
;
; multiply function
; R0 = first number
; R1 = second number
MUL     ; if R1 is 0, return R1
        LDR     R1, R1, #0
        BRz     endMZ
; save registers
        ADD     R6, R6, #-1 ; store R2
        STR     R2, R6, #0  ; onto the stack
;
        LDR     R2, R0, #0  ; load R0 into R2
        ADD     R1, R1, #-1 ; if we want 10 times, we need to do it 9 times
;
repMUL  ADD     R0, R0, R2
        ADD     R1, R1, #-1
        BRp     repMUL
;
; restore registers
        LDR     R2, R6, #0  ; restore R2
        ADD     R6, R6, #1  ; from the stack
        RET
;
endMZ   LDR     R0, R1, #0
        RET
;
;
; takes modulo of two arguments, R0 and R1
; returns 0 if mod-R1 = 0, else returns
; a negative number
; you COULD add R1 back to R0 to get the rest
; aka. a correct modulo
MOD     NOT     R1, R1
        ADD     R1, R1, #1
repM    ADD     R0, R0, R1
        BRp     repM
        RET
;
        .END