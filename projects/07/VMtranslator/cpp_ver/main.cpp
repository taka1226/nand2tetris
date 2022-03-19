#include <iostream>
#include "Parser.hpp"

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << "コマンド引数を正しく設定してください" << std::endl;
        return 0;
    }
    MyClass::Parser parser(argv[1]);

    do{
        VmCodeInfo vm_code_info;
        parser.advance();
        parser.parse(vm_code_info);
        std::cout << &vm_code_info << std::endl;
    }
    while ( !parser.hasMoreLines() );


    return 0;
}
