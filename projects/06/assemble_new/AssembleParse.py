import re

class AssembleParse:
    line = 'None'
    instr_type = 'None'   # A or C
    dest = 'None'
    comp = 'None'
    jump = 'None'
    address = 'None'

    def __init__(self, line):  #line is one line content
        self.line = line

    def parse(self):
        # C type instruction
        c_type_pattern1 = '(.*)\=(.*)'
        c_type_pattern2 = '(.*)\;(.*)'
        c_type_pattern3 = '(.*)\=(.*)\;(.*)'
        # A type instruction
        a_type_pattern = '\@(\w+)'

        # D=M;JLT
        if (re.match(c_type_pattern3, self.line)):
            self.instr_type = 'C'
            self.dest = re.match(c_type_pattern3, self.line).group(1)
            self.comp = re.match(c_type_pattern3, self.line).group(2)
            self.jump = re.match(c_type_pattern3, self.line).group(3)
        # D=M
        elif (re.match(c_type_pattern1, self.line)):
            self.instr_type = 'C'
            self.dest = re.match(c_type_pattern1, self.line).group(1)
            self.comp = re.match(c_type_pattern1, self.line).group(2)
        # D;JLT
        elif (re.match(c_type_pattern2, self.line)):
            self.instr_type = 'C'
            self.comp = re.match(c_type_pattern2, self.line).group(1)
            self.jump = re.match(c_type_pattern2, self.line).group(2)

        # A instr type
        elif (re.match(a_type_pattern, self.line)):
            self.instr_type = 'A'
            self.address = re.match(a_type_pattern, self.line).group(1)
