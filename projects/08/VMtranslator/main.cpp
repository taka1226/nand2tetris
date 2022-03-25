#include <iostream>
#include "Parser.hpp"
#include "CodeWriter.hpp"

extern std::map<std::string, std::string> RegisterTable;
extern std::map<std::string, char> ArithmeticTable;
extern std::map<std::string, std::string> cmpTable;


int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << "コマンド引数を正しく設定してください" << std::endl;
        return 0;
    }
    MyClass::Parser parser(argv[1]);
    MyClass::CodeWriter code_writer(argv[1]);
    do{
        VmCodeInfo vm_code_info;
        parser.advance();
        if (!parser.hasMoreLines()) return 0;

        parser.parse(vm_code_info); //vm_code_info がパースされた

        if (!parser.isSkip()){
            code_writer.Write(vm_code_info);
        }

    }
    while ( parser.hasMoreLines() );


    return 0;
}
