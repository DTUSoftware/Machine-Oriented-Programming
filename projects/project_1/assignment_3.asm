; function to check if a given number in
; R0 is a prime number

isPrime ;save registers
        ADD     R6, R6, #-1 ; store R1
        STR     R1, R6, #0  ; onto the stack
        ADD     R6, R6, #-1 ; store R2
        STR     R2, R6, #0  ; onto the stack
;
; check if R0 is 2
        ADD     R0, R0, #-2 ; check if R0
        BRz     YES         ; is equal to 2
        ADD     R0, R0, #2  ; restore R0
;
; check mod-2 of R0
        ADD     R6, R6, #-1 ; store R0
        STR     R0, R6, #0  ; onto the stack
        LD      R1, R1, #2  ; set second argument to 2
        JMP     MOD;
        ADD     R0, R0, #0
        BRnp    NO
;
; check if prime number
checkP  

NO      AND     R0, R0, #0
        BRnzp   RESTORE
;
YES     LD      R0, R0, #1
;
RESTORE LDR     R1, R6, #0  ; restore R1
        ADD     R6, R6, #1  ; from the stack
        LDR     R2, R6, #0  ; restore R2
        ADD     R6, R6, #1  ; from the stack
        RET

;
; multiply function
; R0 = first number
; R1 = second number
MUL     ; save registers
        ADD     R6, R6, #-1 ; store R2
        STR     R2, R6, #0  ; onto the stack
;
        LD      R2, R0, #0
        ADD     R1, R1, #-1  ; if we want 10 times, we need to do it 9 times
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