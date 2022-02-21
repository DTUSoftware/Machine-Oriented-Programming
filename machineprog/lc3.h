#ifndef __LC3_H
#define __LC3_H
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "binary.h"

    typedef enum {
        ADD = 0001,
        AND = 0101,
        BR = 0000,
        JMP = 1100,
        RET = 1100,
        JSR = 0100,
        JSRR = 0100,
        LD = 0010,
        LDI = 1010,
        LDR = 0110,
        LEA = 1110,
        NOT = 1001,
        RTI = 1000,
        ST = 0011,
        STI = 1011,
        STR = 0111,
        TRAP = 1111,
        UNUSED = 1101
    } Opcode;



    Opcode getOpcode(BinaryWord* binary) {
        if (binary->length != 4) {
            printf("Not a valid opcode.");
            return UNUSED;
        }


//        for (int opcode = ADD; opcode <= UNUSED; opcode++) {
//            switch (opcode) {
//                case ADD:
//                    printf("%d\n", ADD);
//                default:
//                    printf("%d\n", opcode);
//            }
//        }

        printf("int: %d\n", binary->bits);
        Opcode opcode = (int) binary->bits;

        return opcode;
    }

    char binaryToAssembly(BinaryWord binary) {

    }

#endif