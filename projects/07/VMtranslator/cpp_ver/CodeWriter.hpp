#pragma once

#include <map>
#include "Parser.hpp"

enum Register {
    LCL,
    ARG,
    THIS,
    THAT
};

const std::map<string, string> RegisterTable =
{
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"}
};

const std::map<string, char> ArithmeticTable =
{
    {"add", '+'},
    {"sub", '-'},
    {"add", '&'},
    {"or", '|'},
    {"not", '!'}
};

const std::map<string, string> cmpTable =
{
    {"eq", "JEQ"},
    {"lt", "JLT"},
    {"GT", "JGT"}
};

namespace MyClass {
    class CodeWriter {
    public:
        CodeWriter(string vm_filename, VmCodeInfo vm_code_info);
        //void SetFileName(); //書き込むファイルの名前を設定する
        void WriteArithmetic(); //算術コマンドをアセンブリに変換する
        void WritePushPop(); //push, pop コマンドをアセンブリに変換する
        //void Write();
    private:
        string vm_filename_;
        VmCodeInfo vm_code_info_;
        int label_num_; //次使われるlabel ナンバーを保存しておく //スタックとおなじ感じ？
    }
}
