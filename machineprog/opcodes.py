import binary


class Opcode:
    binary = None
    comment = ""

    # Some standard locations used in instructions
    DR = [11, 9]
    SR = [11, 9]
    SR1 = [8, 6]
    SR2 = [2, 0]
    BaseR = [8, 6]
    Imm5 = [4, 0]
    offset5 = [4, 0]
    trapvect8 = [7, 0]
    PCoffset9 = [8, 0]
    PCoffset11 = [10, 0]

    def __init__(self, opcode: str):
        self.opcode = opcode

    def get_name(self):
        return type(self).__name__

    def set_binary(self, binary):
        self.binary = binary

    def remove_binary(self):
        self.binary = None

    def bit(self, bit):
        if self.binary:
            return self.binary[abs(bit-15)]
        return None

    def bits(self, start, end):
        if self.binary:
            return self.binary[abs(start-15):abs(end-15)+1]
        return None

    def is_valid(self):
        return self.bits(15, 12) == self.opcode

    def get_binary_comment(self):
        self.comment = self.get_name()
        # self.comment = self.comment + self.binary[abs(12-15):]
        return self.comment


class ADD(Opcode):
    def __init__(self):
        super().__init__("0001")

    def get_binary_comment(self):
        self.comment = str("R"+str(binary.binary_to_decimal(self.bits(self.DR[0], self.DR[1]))) + " <- " +
                       "R"+str(binary.binary_to_decimal(self.bits(self.SR1[0], self.SR1[1]))) + "+")
        if self.bit(5) == "0":
            self.comment = self.comment + "R"+str(binary.binary_to_decimal(self.bits(self.SR2[0], self.SR2[1])))
        else:
            self.comment = self.comment + "#"+str(binary.binary_to_decimal(self.bits(self.Imm5[0], self.Imm5[1])))
        return self.comment


class AND(Opcode):
    def __init__(self):
        super().__init__("0101")


class BR(Opcode):
    n = 11
    z = 10
    p = 9

    def __init__(self):
        super().__init__("0000")


class JMP(Opcode):
    def __init__(self):
        super().__init__("1100")

    def is_valid(self):
        return super().is_valid() and self.bits(self.BaseR[0], self.BaseR[1]) != "111"


class RET(Opcode):
    def __init__(self):
        super().__init__("1100")

    def is_valid(self):
        return super().is_valid() and self.bits(self.BaseR[0], self.BaseR[1]) == "111"


class JSR(Opcode):
    def __init__(self):
        super().__init__("0100")

    def is_valid(self):
        return super().is_valid() and self.bit(11) == "1"


class JSRR(Opcode):
    def __init__(self):
        super().__init__("0100")

    def is_valid(self):
        return super().is_valid() and self.bit(11) == "0"


class LD(Opcode):
    def __init__(self):
        super().__init__("0010")


class LDI(Opcode):
    def __init__(self):
        super().__init__("1010")


class LDR(Opcode):
    def __init__(self):
        super().__init__("0110")


class LEA(Opcode):
    def __init__(self):
        super().__init__("1110")


class NOT(Opcode):
    SR = [8, 6]

    def __init__(self):
        super().__init__("1001")


class RTI(Opcode):
    def __init__(self):
        super().__init__("1000")


class ST(Opcode):
    def __init__(self):
        super().__init__("0011")


class STI(Opcode):
    def __init__(self):
        super().__init__("1011")


class STR(Opcode):
    def __init__(self):
        super().__init__("0111")


class TRAP(Opcode):
    def __init__(self):
        super().__init__("1111")


class UNUSED(Opcode):
    def __init__(self):
        super().__init__("1101")


opcodes = [
    ADD(), AND(), BR(), JMP(),
    RET(), JSR(), JSRR(), LD(), LDI(),
    LDR(), LEA(), NOT(), RTI(), ST(),
    STI(), STR(), TRAP(), UNUSED()
]


def get_opcode(binary):
    for opcode in opcodes:
        opcode.set_binary(binary)
        if opcode.is_valid():
            return opcode
        else:
            opcode.remove_binary()
    return None


# ADD = 0001,
# AND = 0101,
# BR = 0000,
# JMP = 1100,
# RET = 1100,
# JSR = 0100,
# JSRR = 0100,
# LD = 0010,
# LDI = 1010,
# LDR = 0110,
# LEA = 1110,
# NOT = 1001,
# RTI = 1000,
# ST = 0011,
# STI = 1011,
# STR = 0111,
# TRAP = 1111,
# UNUSED = 1101