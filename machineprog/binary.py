import numpy as np


def printb(binary: str):
    print(pybin_to_bin(binary))


def pybin_to_bin(binary: str):
    if len(binary) >= 2:
        if binary[:2] == "0b":
            binary = binary[2:]
    return binary


def bin_to_pybin(binary: str):
    return "0b"+binary


def binary2c_padding(binary: str, bits: int):
    pybin = False
    if binary[:2] == "0b":
        binary = pybin_to_bin(binary)
        pybin = True

    if int(binary[0]) == 0:
        binary = binary.zfill(bits)
    else:
        binary = binary.rjust(bits, "1")

    if pybin:
        binary = bin_to_pybin(binary)

    return binary


def binary2c_flip(binary: str):
    """
    Flips the 2's complement to make positive negative,
    and negative positive.
    Uses the shortcut method.

    :param binary: The 2's complement
    :return binary: The 2's complement
    """
    py_bin = False
    if binary[:2] == "0b":
        py_bin = True
        binary = pybin_to_bin(binary)

    first_1 = False
    for bit_index in range(len(binary)-1, -1, -1):
        if not first_1:
            if int(binary[bit_index]) == 1:
                first_1 = True
        else:
            if int(binary[bit_index]) == 1:
                binary = binary[:bit_index] + "0" + binary[bit_index+1:]
            else:
                binary = binary[:bit_index] + "1" + binary[bit_index+1:]

    if py_bin:
        binary = bin_to_pybin(binary)

    return binary


def binary2c_flip_alt(binary: str):
    """
    Flips the 2's complement to make positive negative,
    and negative positive.
    Uses the flip all and add one method.

    :param binary: The 2's complement
    :return binary: The 2's complement
    """
    return binary


def decimal_to_binary2c(decimal: int, bits: int = None):
    """
    Returns the 2's complement of the decimal,
    using the subtract powers of two method.
    """

    def largest_power_of_two(decimal: int):
        highest_power_of_two = 0
        for i in range(decimal, 0, -1):
            # If it is a power of 2
            if (i & (i - 1)) == 0:
                highest_power_of_two = i
                break
        return highest_power_of_two

    neg = decimal < 0
    if neg:
        decimal = np.abs(decimal)

    binary = ''
    ones = []
    while decimal > 0:
        largest_power = largest_power_of_two(decimal)
        ones.append(int(np.log2(largest_power)))
        decimal = decimal - largest_power

    binary = binary.zfill(ones[0])
    for i in ones:
        binary = binary[:i] + "1" + binary[i+1:]

    # step 4, part 1. Append 0
    binary = "0" + binary

    # if it was neg, use two's complement shortcut to make negative
    if neg:
        binary = binary2c_flip(binary)

    # make sure the byte size has the correct amount of bits
    if bits:
        binary = binary2c_padding(binary, bits)

    return bin_to_pybin(binary)


def decimal_to_binary2c_division(decimal: int, bits: int = None):
    """
    Returns the 2's complement of the decimal,
    using the division method.
    """
    neg = decimal < 0
    if neg:
        decimal = np.abs(decimal)

    binary = ''

    while decimal > 0:
        remainder = decimal % 2
        # print("dividing " + str(decimal) + " by 2 - mod: " + str(remainder))
        decimal = decimal // 2
        binary = str(remainder) + binary

    # step 4, part 1. Append 0
    binary = "0" + binary

    # if it was neg, use two's complement shortcut to make negative
    if neg:
        binary = binary2c_flip(binary)

    # make sure the byte size has the correct amount of bits
    if bits:
        binary = binary2c_padding(binary, bits)

    return bin_to_pybin(binary)


def binary_to_decimal(binary: str):
    """Returns the decimal value of the binary given."""
    if binary.startswith("0b"):
        return int(binary[2:], 2)
    else:
        return int(binary, 2)


def decimal_to_binary(decimal: int):
    """Returns the binary string of the decimal value given."""
    return bin(decimal)


def adu(binary_1: str, binary_2: str):
    """Adds two binary strings together."""
    return


def binary_to_hex(binary: str):
    return hex(binary_to_decimal(binary))


ADU = adu
