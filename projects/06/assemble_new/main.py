from AssembleParse import AssembleParse
from MachineCode import MachineCode
from SymbolHandler import SymbolHandler
import re

def sanitize_file(file):
    lineContents = [];
    while True:
        line = file.readline()
        if line:
            if line == '\n':
                continue
            elif re.match('\/\/(.*)', line):
                continue
            else:
                if (re.match('(.*)\/\/(.*)', line)):
                    line = re.match('(.*)\/\/(.*)', line).group(1)
            line = line.replace(' ', '').replace('\n', '')
            lineContents.append(line)
        else:
            break
    file.close()
    return lineContents

def labelAddToSymbolTable(lineContents, symbol_handler):
    i = 0
    for line in lineContents:
        if (re.match('\((.*)\)', line)):
            label_name = re.match('\((.*)\)', line).group(1)
            symbol_handler.addEntry(label_name, i)
        else:
            i += 1
    return

def translateSymbolNameToAddress(lineContents, symbol_handler):
    var_addr = 16
    for i in range(len(lineContents)):
        line = lineContents[i]
        if (re.match('\@(.*)', line)):
            if (re.match('@(\d+)', line)):
                continue
            else:
                symbol_name = re.match('\@(.*)', line).group(1)
                if (not symbol_handler.contains(symbol_name)):
                    symbol_handler.addEntry(symbol_name, var_addr)
                    var_addr += 1
                symbol_address = symbol_handler.getValue(symbol_name)
                lineContents[i] = '@' + str(symbol_address)

    return lineContents


def main():
    # f = open("../rect/Rect.asm", 'r')
    #f = open("../pong/Pong.asm", 'r')
    # f = open("../max/Max.asm", 'r')
    f = open("../add/Add.asm", 'r')
    lineContents = sanitize_file(f)
    symbol_handler = SymbolHandler()
    labelAddToSymbolTable(lineContents, symbol_handler)
    lineContents = translateSymbolNameToAddress(lineContents, symbol_handler)

    for line in lineContents:
        if (re.match('\((.*)\)', line)):
            continue
        else:
            assemble_parse = AssembleParse(line)
            assemble_parse.parse()

            machine_code = MachineCode(assemble_parse)
            machine_code.translate()
            print(machine_code.machine_code)

    f.close()

if __name__ == '__main__':
    main()

# assemble_parse = AssembleParse(line)
# assemble_parse.parse()
#
# machine_code = MachineCode(assemble_parse)
# machine_code.translate()
# print(machine_code.machine_code)
