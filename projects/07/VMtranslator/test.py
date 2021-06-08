s = "/home/takahiro/documents/nand2tetris/projects/07/VMtranslator/submit/lang.txt"

t = s.split("/")
path = ""
for i in range(len(t) - 1):
    u = t[i]
    path += u + "/"
print(path)
