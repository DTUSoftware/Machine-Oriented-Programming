class Binary:
    def __init__(self, binary: str = "", bits: int = 8):
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
        for i in range(len(self.binary)):
            self.binary_array.append(self.binary[i])

    def update_binary_from_array(self):
        self.binary = ""
        for i in range(len(self.binary_array)):
            self.binary = self.binary + self.binary_array[i]

    def flip(self):
        for i in range(len(self.binary_array)):
            if self.binary_array[i] == "1":
                self.binary_array[i] = "0"
            else:
                self.binary_array[i] = "1"
        self.update_binary_from_array()

    def add(self, binary):
        carry_on = False
        added = False
        for i in range(len(self.binary_array)):
            j = abs(i - len(self.binary_array)) - 1
            k = abs(i - len(binary.binary_array)) - 1
            if k > len(binary.binary_array) or k < 0:
                added = True

            # print(f"i: {i}, j: {j}, k: {k}")

            count = 0
            if self.binary_array[j] == "1":
                count += 1
            if not added and binary.binary_array[k] == "1":
                count += 1
            if carry_on:
                count += 1

            carry_on = False
            if count == 1:
                self.binary_array[j] = "1"
            elif count == 2:
                self.binary_array[j] = "0"
                carry_on = True
            elif count == 3:
                self.binary_array[j] = "1"
                carry_on = True
        self.update_binary_from_array()

    def invert(self):
        self.flip()
        self.add(Binary("1"))

    def pad(self):
        if self.binary and len(self.binary) < self.bits:
            if self.binary[0] == "0":
                self.binary = self.binary.zfill(self.bits)
            else:
                self.binary = self.binary.rjust(self.bits, "1")


class Hex:
    def __init__(self, hex: str = ""):
        self.hex = hex

    def set_hex_from_decimal(self, decimal: int):
        self.hex = hex(decimal)[2:]


if __name__ == "__main__":
    binary = Binary("00101")
    print(binary.binary)
    binary.invert()
    print(binary.binary)

    binary2 = Binary()
    binary2.set_binary_from_decimal(104)
    print(binary2.binary)
    binary2.set_binary_from_decimal(-104)
    print(binary2.binary)

    hexNum = Hex()
    hexNum.set_hex_from_decimal(86)
    print(hexNum.hex)


