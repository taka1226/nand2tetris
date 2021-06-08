#pointer が不完全
class CodeWriter:
    def __init__(self, filename):
        self.filename = filename
        self.label_num = 0
        self.registerTable = {
            'local': 'LCL',
            'argument': 'ARG',
            'this': 'THIS',
            'that': 'THAT',
        }


    def setVmParser(self, vm_parser):
        self.vm_parser = vm_parser
        if (vm_parser.register in self.registerTable):
            self.register = self.registerTable[vm_parser.register]
        else:
            self.register = vm_parser.register

    def getNewLabel(self):
        self.label_num += 1
        return "LABEL" + str(self.label_num)

    def popTempIntoAsm(self):
        pop_temp = """
// pop {0} {1}
@5
D=A
@{1}
A=D+A
D=A
@addr
M=D
@SP
M=M-1
A=M
D=M
@addr
A=M
M=D
""".format(self.vm_parser.register, self.vm_parser.address)
        return pop_temp

    def pushTempIntoAsm(self):
        push_temp = """
//push {0} {1}
@5  //base addr
D=A
@{1}
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1
""".format(self.vm_parser.register, self.vm_parser.address)
        return push_temp

    def popIntoAsm(self):   # vm_parser.register = argument or local or this or that で使用
        #修正完了
        pop_pattern = """
// pop {0} {1}
@{0}
D=M
@{1}
A=D+A
D=A
@addr
M=D
@SP
M=M-1
A=M
D=M
@addr
A=M
M=D
"""
        #修正完了
        pop_static_pattern = """
//pop static {0}
@SP
M=M-1
A=M
D=M
@{1}.{0}
M=D
"""

        if (self.vm_parser.register == "static"):
            pop_asm = pop_static_pattern.format(self.vm_parser.address, self.filename)
        elif (self.vm_parser.register == "pointer"):
            pop_asm = self.pointerPopIntoAsm()
        elif (self.vm_parser.register == "temp"):
            pop_asm = self.popTempIntoAsm()
        else:
            pop_asm = pop_pattern.format(self.register, self.vm_parser.address)
        return pop_asm

    def pushIntoAsm(self): # vm_parser.register が static以外で使用
        #修正完了
        push_pattern = """
//push {0} {1}
@{0}  //base addr
D=M
@{1}
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1
"""
        #修正完了
        push_constant_pattern = """
//push constant {0}
@{0}
D=A
@SP
A=M
M=D
@SP
M=M+1
"""
        #修正完了
        push_static_pattern = """
//push static {0}
@{1}.{0}
D=M
@SP
A=M
M=D
@SP
M=M+1
"""

        if (self.vm_parser.register == "constant"):
            push_asm = push_constant_pattern.format(self.vm_parser.address)
        elif (self.vm_parser.register == "static"):
            push_asm = push_static_pattern.format(self.vm_parser.address, self.filename)
        elif (self.vm_parser.register == "pointer"):
            push_asm = self.pointerPushIntoAsm();
        elif (self.vm_parser.register == "temp"):
            push_asm = self.pushTempIntoAsm()
        else:
            push_asm = push_pattern.format(self.register, self.vm_parser.address)
        return push_asm


    def codeOutput(self):
        if (self.vm_parser.command == "pop"):
            return self.popIntoAsm()
        elif (self.vm_parser.command == "push"):
            return self.pushIntoAsm()
        elif (self.vm_parser.command == "add"):
            return self.addIntoAsm()
        elif (self.vm_parser.command == "sub"):
            return self.subIntoAsm()
        elif (self.vm_parser.command == "neg"):
            return self.negIntoAsm()
        elif (self.vm_parser.command == "eq" or self.vm_parser.command == "gt" or self.vm_parser.command == "lt"):
            return self.compareIntoAsm()
        elif (self.vm_parser.command == "and" or self.vm_parser.command == "or" or self.vm_parser.command == "not"):
            return self.bitOpIntoAsm()
        return 1    # error

    def addIntoAsm(self):
        #修正完了
        add_asm = """
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
@SP
A=M
M=D
@SP
M=M+1
"""
        return add_asm

    def subIntoAsm(self):
        #修正完了
        sub_asm = """
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SP
A=M
M=D
@SP
M=M+1
"""
        return sub_asm

    def negIntoAsm(self):
        #修正完了
        neg_asm = """
@SP
M=M-1
A=M
M=-M
@SP
M=M+1
"""
        return neg_asm

    def compareIntoAsm(self):
        new_label = self.getNewLabel()
        new_label2 = self.getNewLabel()
        #修正完了
        compare_pattern = """
@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@{0}
D;{1}
@SP
A=M
M=0
@{2}
0;JMP
({0})
    @SP
    A=M
    M=-1
({2})
    @SP
    M=M+1

"""

        if (self.vm_parser.command == "eq"):
            compare = "JEQ"
        elif (self.vm_parser.command == "gt"):
            compare = "JGT"
        elif (self.vm_parser.command == "lt"):
            compare = "JLT"

        compare_asm = compare_pattern.format(new_label, compare, new_label2)
        return compare_asm


    def bitOpIntoAsm(self):
        #修正完了
        bit_op_pattern = """
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
{0}
@SP
M=M+1
"""
        if (self.vm_parser.command == "and"):
            opr = "M=M&D"
            return bit_op_pattern.format(opr)
        elif (self.vm_parser.command == "or"):
            opr = "M=M|D"
            return bit_op_pattern.format(opr)
        elif (self.vm_parser.command == "not"):
            #修正完了
            not_asm = """
@SP
M=M-1
A=M
M=!M
@SP
M=M+1
"""
            return not_asm
        return 1

    def pointerPushIntoAsm(self):
        address = None
        if (self.vm_parser.address == '0'):
            address = 'THIS'
        elif (self.vm_parser.address == '1'):
            address = 'THAT'
        pointer_asm = """
//push pointer {0}
@{0}
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1
""".format(address)
        return pointer_asm

    def pointerPopIntoAsm(self):
        address = None
        if (self.vm_parser.address == '0'):
            address = 'THIS'
        elif (self.vm_parser.address == '1'):
            address = 'THAT'
        pop_asm = """
//pop pointer {0}
@SP
M=M-1
A=M
D=M
@{0}
A=M
M=D
""".format(address)

        return pop_asm
