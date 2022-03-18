; reads two seperate digits from the input, and makes it into a decimal number
;
; input: two digits read from input I/O device
; output: R0 - the decimal number
readS   ADD     R6, R6, #-1 ; store used registers onto the stack
        STR     R1, R6, #0
        ADD     R6, R6, #-1
        STR     R2, R6, #0
        ADD     R6, R6, #-1
        STR     R3, R6, #0
        ADD     R6, R6, #-1
        STR     R4, R6, #0
        ADD     R6, R6, #-1
        STR     R5, R6, #0
;
; prints console initial output
        LD      R5, ASCII
        LEA     R0, PROMPT
        TRAP    x22
        LEA     R0, NEWLINE
        TRAP    x21
        AND     R4, R4, #0
        ADD     R4, R4, #2      ; COUNTER
;
READ    AND     R0, R0, #0
        TRAP    x23             ; read
        TRAP    x21             ; print
        ADD     R0, R0, R5
        ADD     R4, R4, #-1
        BRnz    LoadR2
        ADD     R1, R0, #0
        BRnzp   READ
LoadR2  ADD     R2, R0, #0
;
        ADD     R0, R1, #0
        AND     R3, R3, #0
        ADD     R3, R3, #9  ; we do it 10 times
MUL     ADD     R0, R0, R1
        ADD     R3, R3, #-1
        BRp     MUL
;
END     ADD     R0, R0, R2
        LDR     R5, R6, #0  ; restore registers from the stack
        ADD     R6, R6, #1
        LDR     R4, R6, #0
        ADD     R6, R6, #1
        LDR     R3, R6, #0
        ADD     R6, R6, #1
        LDR     R2, R6, #0
        ADD     R6, R6, #1
        LDR     R1, R6, #0
        ADD     R6, R6, #1
        RET
;
NEWLINE .FILL x000A
ASCII   .FILL xFFD0 ; inverse of x0030
PROMPT  .STRINGZ "Input a 2 digit decimal number:"