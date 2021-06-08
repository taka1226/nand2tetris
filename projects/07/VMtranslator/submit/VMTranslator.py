#!/usr/bin/python3
from VmParser import VmParser
from CodeWriter import CodeWriter
import argparse
import re
import os

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
            line = line.replace('\n', '')
            lineContents.append(line)
        else:
            break
    file.close()
    return lineContents


def main():
    arg_parser = argparse.ArgumentParser(description='vm translator')
    arg_parser.add_argument('arg1', help='file path')
    args = arg_parser.parse_args()
    file_path = args.arg1
    f = open(file_path, 'r')
    lineContents = sanitize_file(f)   # lineContents は 配列になっている
    f.close()

    t = file_path.split("/")
    path = ""
    for i in range(len(t) - 1):
        u = t[i]
        path += u + "/"
    filename = os.path.splitext(os.path.basename(file_path))[0]   # filename is without extension

    g = open(path + filename + ".asm", "w")

    code_writer = CodeWriter(filename)
    for line in lineContents:
        vm_parser = VmParser(line)
        vm_parser.parser()
        code_writer.setVmParser(vm_parser)
        code = code_writer.codeOutput()
        g.write(code)
    g.close()
    return

if __name__ == '__main__':
    main()
