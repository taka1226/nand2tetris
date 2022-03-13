#pragma once

#include "Parser.hpp"

namespace MyClass {
    class CodeWriter {
    public:
        CodeWriter(string vm_filename, VmCodeInfo vm_code_info);
        void SetFileName(); //書き込むファイルの名前を設定する
        void WriteArithmetic(); //算術コマンドをアセンブリに変換する
        void WritePushPop(); //push, pop コマンドをアセンブリに変換する
        void Write();
    private:
        string vm_filename_;
        VmCodeInfo vm_code_info_;
    }
}
