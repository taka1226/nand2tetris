class MachineCode:
    assemble_parse = None
    machine_code = None
    TransTable = {
        'dest':{
            "None":"000",
            "M":"001",
            "D":"010",
            "MD":"011",
            "A":"100",
            "AM":"101",
            "AD":"110",
            "AMD":"111",
        },
        'comp':{
            "0":"0101010",
            "1":"0111111",
            "-1":"0111010",
            "D":"0001100",
            "A":"0110000",
            "!D":"0001101",
            "!A":"0110001",
            "-D":"0001111",
            "-A":"0110011",
            "D+1":"0011111",
            "A+1":"0110111",
            "D-1":"0001110",
            "A-1":"0110010",
            "D+A":"0000010",
            "D-A":"0010011",
            "A-D":"0000111",
            "D&A":"0000000",
            "D|A":"0010101",
            "M":"1110000",
            "!M":"1110001",
            "-M":"1110011",
            "M+1":"1110111",
            "M-1":"1110010",
            "D+M":"1000010",
            "D-M":"1010011",
            "M-D":"1000111",
            "D&M":"1000000",
            "D|M":"1010101",
        },
        'jump': {
            "None":"000",
            "JGT":"001",
            "JEQ":"010",
            "JGE":"011",
            "JLT":"100",
            "JNE":"101",
            "JLE":"110",
            "JMP":"111",
        }
    }
    def __init__(self, assemble_parse):
        self.assemble_parse = assemble_parse

    def translate(self):
        if (self.assemble_parse.instr_type == 'C'):
            comp = self.assemble_parse.comp
            dest = self.assemble_parse.dest
            jump = self.assemble_parse.jump

            comp_translated = self.TransTable['comp'][comp]
            dest_translated = self.TransTable['dest'][dest]
            jump_translated = self.TransTable['jump'][jump]

            self.machine_code = '111' + comp_translated + dest_translated + jump_translated
        elif (self.assemble_parse.instr_type == 'A'):
            bin_address_sized = self.getAddressBin(self.assemble_parse.address)
            self.machine_code  = '0' + bin_address_sized

    def getAddressBin(self, address):
        if (type(address) == str):
            address = int(address)
        total_address_length = 15
        bin_address = ''
        while (True) :
            remainder = address % 2
            bin_address += str(remainder)
            if (address <= 1):
                break
            address = address // 2

        bin_address_sized = '0' * (total_address_length - len(bin_address)) + bin_address[::-1]
        return bin_address_sized
