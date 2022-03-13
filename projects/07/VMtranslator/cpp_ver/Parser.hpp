#pragma once

#include <string>

enum CommandType {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
};

//vmcode の一行の情報
struct VmCodeInfo {
    CommandType command_type;
    string arg1; //C_ARITHMETIC の場合はコマンド、push pop の場合はセグメント名
    int arg2;
};

namespace MyClass {
    class Parser {
    public:
        Parser(string vm_filename); //constructor
        bool hasMoreLines();  //まだ命令が残っているかどうか
        void ReadOneLineFromVmFile(); //Vm ファイルから一行を読み取る
        VmcodeInfo getVmCodeInfo(); //パースする

    private:
        string vm_filename_;
        string line_; //vmCode 1行
        VmCodeInfo vm_code_info_;
    }
}
