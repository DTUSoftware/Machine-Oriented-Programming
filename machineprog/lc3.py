import opcodes


def convert_binary(binary):
    binary_words = code.split("\n")
    words_with_comments = []
    for binary in binary_words:
        opcode = opcodes.get_opcode(binary)
        comment = opcode.get_binary_comment()
        words_with_comments.append(binary + "  " + comment)

    new_file = "\n".join(words_with_comments)
    return new_file


if __name__ == "__main__":
    # add = opcodes.ADD()
    #
    # add.set_binary("0001001001000011")
    # print(add.get_binary_comment())

    code = str(
        "0101000000100000\n"+
        "0010001000000101\n"+
        "0000110000000011\n"+
        "0001000000000001\n"+
        "0001001001111111\n"+
        "0000111111111100\n"+
        "1111000000100101\n"+
        "0000000000001010"
    )

    new_file = convert_binary(code)
    print(new_file)

