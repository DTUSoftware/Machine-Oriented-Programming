class Binary:
    def __init__(self, binary: str = "0", bits: int = 8):
        self.binary = binary
        self.bits = bits
        self.binary_array = []

        self.set_binary(binary)

    def set_binary_from_decimal(self, decimal: int):
        neg = decimal < 0
        if neg:
            decimal = abs(decimal)

        binary = ""

        while decimal > 0:
            remainder = decimal % 2
            # print("dividing " + str(decimal) + " by 2 - mod: " + str(remainder))
            decimal = decimal // 2
            binary = str(remainder) + binary

        # step 4, part 1. Append 0
        binary = "0" + binary

        self.set_binary(binary)

        if neg:
            self.invert()

    def set_binary(self, binary: str):
        self.binary = binary
        self.pad()
        self.update_binary_array()

    def update_binary_array(self):
        self.binary_array = []
        for i in range(self.bits):
            self.binary_array.append(self.binary[i])

    def update_binary_from_array(self):
        self.binary = ""
        for i in range(self.bits):
            self.binary = self.binary + self.binary_array[i]

    def flip(self):
        for i in range(self.bits):
            if self.binary_array[i] == "1":
                self.binary_array[i] = "0"
            else:
                self.binary_array[i] = "1"
        self.update_binary_from_array()

    def add(self, binary):
        # make both binary ops same size
        if self.bits != binary.bits:
            if self.bits > binary.bits:
                binary.bits = self.bits
                binary.pad()
                binary.update_binary_array()
            else:
                self.bits = binary.bits
                self.pad()
                self.update_binary_array()

        operands_are_same = self.binary[0] == binary.binary[0]
        same_operand = self.binary[0]

        carry_on = False
        for i in range(self.bits - 1, -1, -1):
            # print(f"i: {i}, j: {j}, k: {k}")
            # print(self.binary_array)
            # print(binary.binary_array)

            count = 0
            if self.binary_array[i] == "1":
                count += 1
            if binary.binary_array[i] == "1":
                count += 1
            if carry_on:
                count += 1

            carry_on = False
            if count == 1:
                self.binary_array[i] = "1"
            elif count == 2:
                self.binary_array[i] = "0"
                carry_on = True
            elif count == 3:
                self.binary_array[i] = "1"
                carry_on = True

        self.update_binary_from_array()

        if operands_are_same and same_operand != self.binary[0]:
            print("OVERFLOW - NUMBERS TOO BIG")

    def subtract(self, binary):
        binary.invert()
        self.add(binary)
        binary.invert()

    def invert(self):
        self.flip()
        self.add(Binary("01"))

    def pad(self):
        if self.binary and len(self.binary) < self.bits:
            if self.binary[0] == "0":
                self.binary = self.binary.zfill(self.bits)
            else:
                self.binary = self.binary.rjust(self.bits, "1")

    def to_decimal(self):
        neg = False
        if self.binary[0] == 1:
            self.invert()
            neg = True

        decimal = 0
        for i in range(len(self.binary)):
            if self.binary[i] == "1":
                # print(f"{decimal} + 2^{abs(i-self.bits)-1}")
                decimal += 2**(abs(i-self.bits)-1)

        if neg:
            decimal = -decimal
            self.invert()

        return decimal

    def print(self):
        binary_string = ""
        j = 0
        for i in range(self.bits-1, -1, -1):
            binary_string = self.binary[i] + binary_string
            j += 1
            if j == 4:
                binary_string = " " + binary_string
        binary_string = binary_string.strip()
        print(binary_string)


class Hex:
    def __init__(self, hex: str = ""):
        self.hex = hex

    def set_hex_from_decimal(self, decimal: int):
        self.hex = hex(decimal)[1:]

    def print(self):
        print(self.hex)


if __name__ == "__main__":
    binary = Binary("00101")
    binary.print()
    binary.invert()
    binary.print()

    binary2 = Binary()
    binary2.set_binary_from_decimal(-104)
    binary2.print()
    binary2.set_binary_from_decimal(104)
    binary2.print()
    print(binary2.to_decimal())

    binary3 = Binary()
    binary3.set_binary_from_decimal(104)
    binary2.subtract(binary3)
    binary2.print()

    hexNum = Hex()
    hexNum.set_hex_from_decimal(86)
    hexNum.print()


