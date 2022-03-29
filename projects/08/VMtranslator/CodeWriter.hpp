#pragma once

#include "Parser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>

enum Register {
    LCL,
    ARG,
    THIS,
    THAT
};


namespace MyClass {
    class CodeWriter {
    public:
        CodeWriter(std::string vm_filename); //書き込むファイルの名前を設定する
        ~CodeWriter();
        void Write(VmCodeInfo vm_code_info);
        void WriteArithmetic(VmCodeInfo vm_code_info); //算術コマンドをアセンブリに変換する
        void WritePushPop(VmCodeInfo vm_code_info); //push, pop コマンドをアセンブリに変換する
        void WriteLabel(VmCodeInfo vm_code_info);
        void WriteGoto(VmCodeInfo vm_code_info);
        void WriteIf(VmCodeInfo vm_code_info);
        void WriteFunction(VmCodeInfo vm_code_info);
        void WriteCall(VmCodeInfo vm_code_info);

    private:
        std::string base_filename_;
        std::ofstream asm_file_;
        int label_num_; //次使われるlabel ナンバーを保存しておく //スタックとおなじ感じ？
    };
}
