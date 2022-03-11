        .ORIG x3000
START   AND     R1, R1, #0
        AND     R2, R2, #0
        AND     R3, R3, #0
        AND     R4, R4, #0
        LD      R0, PROMPT
        TRAP    x24
        LD      R0, NEWLINE
        TRAP    x24
        ADD     R4, R4, #2          ; COUNTER
;
READ    TRAP    x23             ; read
        TRAP    x21             ; print
        ADD     R0, R0, ASCII
        ADD     R4, R4, #-1
        BRnz    R2
        LD      R1, R0
        BRnzp   READ
R2      LD      R2, R0

MUL
        TRAP x25
;
NEWLINE .FILL x000A
ASCII   .FILL x0030
PROMPT  .STRINGZ ´´Input a 2 digit decimal number:´´
        .END