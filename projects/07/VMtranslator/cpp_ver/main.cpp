#include <iostream>
#include "Parser.hpp"

int main(){
    MyClass::Parser parser("test.vm");

    do{
        VmCodeInfo vm_code_info;
        parser.advance();
        parser.parse(vm_code_info);
        std::cout << &vm_code_info << std::endl;
    }
    while ( !parser.hasMoreLines() );


    return 0;
}
