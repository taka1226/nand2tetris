#pragma once

#include <string>
#include <fstream>

enum CommandType {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
};

//vmcode の一行の情報
struct VmCodeInfo {
    CommandType command_type;
    std::string arg1; //C_ARITHMETIC の場合はコマンド、push pop の場合はセグメント名
    int arg2;
};

namespace MyClass {
    class Parser {
    public:
        Parser(std::string& vm_filename); //constructor
        bool hasMoreLines();  //まだ命令が残っているかどうか
        void advance(); //Vm ファイルから一行を読み取る
        VmCodeInfo parse(); //パースする

    private:
        std::ifstream* vm_file_;
        std::string line_; //vmCode 1行
    };
}
