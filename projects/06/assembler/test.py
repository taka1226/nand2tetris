# def getAddressBin(address):
#     total_address_length = 15
#     bin_address = ''
#     while (True) :
#         bin_address += str(address % 2)
#         if (address // 2 == 1):
#             bin_address += str(1)
#             break
#         address = address // 2
#
#     bin_address_sized = '0' * (total_address_length - len(bin_address)) + bin_address[::-1]
#     return bin_address_sized
#
#
# s = getAddressBin(12)
# print(s)
#
#


from AssembleParse import AssembleParse
from MachineCode import MachineCode

assemble_parse = AssembleParse("M=-1")
assemble_parse.parse()

machine_code = MachineCode(assemble_parse)
machine_code.translate()
print(machine_code.machine_code)
print(assemble_parse.dest)
print(assemble_parse.comp)
print(assemble_parse.jump)
print(assemble_parse.instr_type)
