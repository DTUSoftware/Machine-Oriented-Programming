#ifndef __BINARY_H
#define __BINARY_H
    #include <string.h>
    #include <stdio.h>

    // The amount of bits that we have per byte
    int BITSIZE = 5;

    // Sets the amount of bits per byte
    void setBits(int bits) {
        int temp_bits = bits;
        {
            extern int BITSIZE;
            BITSIZE = temp_bits;
        }
        
    }

    // Gets the amount of bits that we use per byte
    int getBits() {
        return BITSIZE;
    }

    // A binary word struct
    struct BinaryWord {
        char *bits;
        int length;
        int current_index;
    };

    // Free a binary word
    void freeBinaryWord(struct BinaryWord binary) {
        free(binary.bits);
    }

    // Prints a binary word
    void printBinary(struct BinaryWord binary) {
        for (int i = 0; i < binary.length; ++i) {
            printf("%c", binary.bits[i]);
        }
    }

    // Gets an empty binary word array
    struct BinaryWord newBinaryWord() {
        struct BinaryWord binary;

        int wordsize = getBits();
        char *bits;
        bits = (char *)malloc(wordsize*sizeof(char));

        if (bits != NULL) {
            binary.bits = bits;
            binary.length = wordsize;
            binary.current_index = binary.length-1;
        }

        return binary;
    }

    // Flips the 2's complement to make positive negative,
    // and negative positive.
    // Uses the shortcut method.
    void flipBinaryWord(struct BinaryWord binary) {
        int first_1 = 0;
        for (int i = binary.length-1; i >= 0; --i) {
            if (first_1 == 0) {
                if (binary.bits[i] == '1') {
                    first_1 = 1;
                }
            }
            else {
                if (binary.bits[i] == '1') {
                    binary.bits[i] = '0';
                }
                else {
                    binary.bits[i] = '1';
                }
            }
        }
        return;
    }

    // Pad a binaryword
    void padBinaryWord(struct BinaryWord binary) {
        if (binary.bits[binary.current_index] == '0') {
            --binary.current_index;
            for (binary.current_index; binary.current_index >= 0; --binary.current_index) {
                binary.bits[binary.current_index] = '0';
            }
        }
        else {
            --binary.current_index;
            for (binary.current_index; binary.current_index >= 0; --binary.current_index) {
                binary.bits[binary.current_index] = '1';
            }
        }
        return;
    }

    // Returns the 2's complement of the decimal,
    // using the division method.
    struct BinaryWord decimalToBinary(int decimal) {
        struct BinaryWord binary = newBinaryWord();

        int neg = 0;
        if (decimal < 0) {
            neg = 1;
            decimal = abs(decimal);
        }

        while (decimal > 0) {
            int remainder = decimal % 2;
            decimal = decimal / 2;
            binary.bits[binary.current_index] = remainder+'0';
            // printf("remainder: %d - decimal: %d\n", remainder, decimal);
            // printf("i: %d - inserted at: %d\n", i, abs(i-(binary.length-1)));
            --binary.current_index;
        }

        // step 4, part 1. Append 0
        binary.bits[binary.current_index] = '0';

        // if it was neg, use two's complement shortcut to make negative
        if (neg == 1) {
            flipBinaryWord(binary);
        }

        // make sure the byte size has the correct amount of bits
        padBinaryWord(binary);
        return binary;
    }

#endif