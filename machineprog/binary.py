import numpy as np


def binary_to_decimal(binary: str):
    """Returns the decimal value of the binary given."""
    return int(binary[2:], 2)


def decimal_to_binary(decimal: int):
    """Returns the binary string of the decimal value given."""
    return bin(decimal)


def adu(binary_1: str, binary_2: str):
    """Adds two binary strings together."""
    return


def binary_to_hex(binary: str):
    return hex(binary_to_decimal(binary))


ADU = adu
