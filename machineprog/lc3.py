import opcodes


def convert_binary(binary):
    binary_words = code.split("\n")
    words_with_comments = []
    for binary in binary_words:
        opcode = opcodes.get_opcode(binary)
        if opcode:
            comment = opcode.get_binary_comment()
            words_with_comments.append(binary + "  ; " + comment)
        else:
            words_with_comments.append(binary)

    new_file = "\n".join(words_with_comments)
    return new_file


if __name__ == "__main__":
    # add = opcodes.ADD()
    #
    # add.set_binary("0001001001000011")
    # print(add.get_binary_comment())

    with open("lc3.txt", "r", encoding="UTF-8") as f:
        code = f.read()
    new_file = convert_binary(code)
    print(new_file)

