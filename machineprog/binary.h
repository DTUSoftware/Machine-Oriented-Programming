#ifndef __BINARY_H
#define __BINARY_H
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    // The amount of bits that we have per byte
    int global_word_size = 5;

    // Sets the amount of bits per byte
    void setBits(int bits) {
        int temp_bits = bits;
        {
            extern int global_word_size;
            global_word_size = temp_bits;
        }
        
    }

    // Gets the amount of bits that we use per byte
    int getBits() {
        return global_word_size;
    }

    // A binary word struct
    typedef struct {
        char *bits;
        int length;
        int current_index;
    } BinaryWord;

    // Free a binary word
    void freeBinaryWord(BinaryWord binary) {
        free(binary.bits);
    }

    // Reset a currentIndex for a binary word
    void resetCurrentIndex(BinaryWord* binary) {
        binary->current_index = (binary->length)-1;
//        printf("Set current index to %d\n", binary->current_index);
    }

    // Prints a binary word
    void printBinary(BinaryWord* binary) {
        for (int i = 0; i < binary->length; ++i) {
            printf("%c", binary->bits[i]);
        }
    }

    // Gets an empty binary word array with given wordsize
    BinaryWord newBinaryWordWithSize(int wordsize) {
        BinaryWord binary;

        char *bits;
        bits = (char *)malloc(wordsize*sizeof(char));

        if (bits != NULL) {
            binary.bits = bits;
            binary.length = wordsize;
            resetCurrentIndex(&binary);
        }
        else {
            printf("COULDN'T ALLOCATE MEMORY TO BINARY WORD!!!!\n");
            binary.bits = NULL;
            binary.length = 0;
        }

//        printf("Created new binary word:\n"
//               "- Length: %d\n"
//               "- CurrentIndex: %d\n",
//               binary.length, binary.current_index);

        return binary;
    }

    // Gets an empty binary word array
    BinaryWord newBinaryWord() {
        return newBinaryWordWithSize(getBits());
    }

    // Flips the 2's complement to make positive negative,
    // and negative positive.
    // Uses the shortcut method.
    void flipBinaryWord(BinaryWord* binary) {
        int first_1 = 0;
        for (int i = (binary->length)-1; i >= 0; --i) {
            if (first_1 == 0) {
                if (binary->bits[i] == '1') {
                    first_1 = 1;
                }
            }
            else {
                if (binary->bits[i] == '1') {
                    binary->bits[i] = '0';
                }
                else {
                    binary->bits[i] = '1';
                }
            }
        }
        return;
    }

    // Pad a binaryword
    void padBinaryWord(BinaryWord* binary) {
        if (binary->bits[binary->current_index] == '0') {
            --binary->current_index;
            for (; binary->current_index >= 0; --binary->current_index) {
                binary->bits[binary->current_index] = '0';
            }
        }
        else {
            --binary->current_index;
            for (; binary->current_index >= 0; --binary->current_index) {
                binary->bits[binary->current_index] = '1';
            }
        }
        return;
    }

    // Returns the 2's complement of the decimal,
    // using the division method.
    //
    // int wordsize: the amount of bits in the binary word
    BinaryWord decimalToBinaryWithSize(int decimal, int wordsize) {
        BinaryWord binary = newBinaryWordWithSize(wordsize);

        int neg = 0;
        if (decimal < 0) {
            neg = 1;
            decimal = abs(decimal);
        }

        while (decimal > 0) {
            int remainder = decimal % 2;
            decimal = decimal / 2;
            binary.bits[binary.current_index] = remainder+'0';
//            printf("remainder: %d - decimal: %d\n", remainder, decimal);
//            printf("i: %d\n", binary.current_index);
            --binary.current_index;
        }

        // step 4, part 1. Append 0
        binary.bits[binary.current_index] = '0';

        // if it was neg, use two's complement shortcut to make negative
        if (neg == 1) {
            flipBinaryWord(&binary);
        }

        // make sure the byte size has the correct amount of bits
        padBinaryWord(&binary);
        return binary;
    }

    // Returns the 2's complement of the decimal,
    // using the division method.
    BinaryWord decimalToBinary(int decimal) {
        return decimalToBinaryWithSize(decimal, getBits());
    }

#endif