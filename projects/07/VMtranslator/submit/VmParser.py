import re

class VmParser:
    lineContent = None
    command = None
    register = None
    address = None
    def __init__(self, lineContent):
        self.lineContent = lineContent


    def parser(self):
        pattern_stack = "(.*)\ (.*)\ (.*)"
        pattern_cmd = "(.*)"

        if (re.match(pattern_stack, self.lineContent)): #pop push command
            self.command = re.match(pattern_stack, self.lineContent).group(1)
            self.register = re.match(pattern_stack, self.lineContent).group(2)
            self.address = re.match(pattern_stack, self.lineContent).group(3)

        elif (re.match(pattern_cmd, self.lineContent)):
            self.command = re.match(pattern_cmd, self.lineContent).group(1)
