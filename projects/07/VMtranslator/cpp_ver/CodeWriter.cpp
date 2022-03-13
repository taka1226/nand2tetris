#include "CodeWriter.hpp"
#include "Parser.hpp"

MyClass::CodeWriter::CodeWriter(string vm_filename, VmCodeInfo vm_code_info)
    : vm_filename_{vm_filename}, vm_code_info_{vm_code_info}

void MyClass::CodeWriter::WriteArithmetic(){

}


void MyClass::CodeWriter::WritePushPop(){
    if (!(vm_code_info_.command_type == C_PUSH || vm_code_info_.command_type == C_POP)){ //push, pop 以外ならば
        printf("only push and pop are allowed!");
        return;
    }


}
