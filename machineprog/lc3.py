import opcodes

if __name__ == "__main__":
    # add = opcodes.ADD()
    #
    # add.set_binary("0001001001000011")
    # print(add.get_binary_comment())

    opcode = opcodes.get_opcode("0001001001000011")
    print(opcode.get_binary_comment())
