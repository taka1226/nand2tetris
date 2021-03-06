#pragma once

#include <string>
#include <fstream>
#include <vector>

enum CommandType {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_COMMENT,
};

//vmcode の一行の情報
struct VmCodeInfo {
    CommandType command_type;
    std::string arg1; //C_ARITHMETIC の場合はコマンド、push pop の場合はセグメント名
    int arg2;
};

namespace MyLibrary{
    std::vector<std::string> split(const std::string& src, const char* delim = " ");

    void deleteNl2(std::string &targetStr);
}

namespace MyClass {
    class Parser {
    public:
        Parser(std::string vm_filename); //constructor
        ~Parser();
        bool hasMoreLines();  //まだ命令が残っているかどうか
        void advance(); //Vm ファイルから一行を読み取る
        void parse(VmCodeInfo& vm_code_info); //パースする

        //テスト用
        void setLine(std::string line);

    private:
        std::ifstream vm_file_;
        std::string line_; //vmCode 1行
    };
}
