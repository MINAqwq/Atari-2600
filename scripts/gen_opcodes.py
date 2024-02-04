#!/usr/bin/python

from sys import argv, stdout

FILE_PATH: str = "src/cpu/opcodes.h"

lines: list[str] = []
opcodes: list[str] = []

try:
        with open(FILE_PATH, "r") as f:
                lines = [line.rstrip() for line in f]
except Exception as e:
        print("run script from repository root :)")

for line in lines:
        if "void OP_" not in line:
                continue

        opcodes.append(line[8] + line[9])

# -p
if len(argv) > 1 and argv[1] == "-p":
        stdout.write(f"{((len(opcodes) / 0x100) * 100):.2f}% (including illegal opcodes)\n")
        exit(0)

stdout.write("op_ptr\nget_opcode(uint8_t op)\n{\n\tswitch(op) {\n")
for op in opcodes:
        stdout.write("\tcase 0x" + op + ":\n\t\treturn &OP_" + op + ";\n")

stdout.write("\t}\n\treturn NULL;\n}\n")
