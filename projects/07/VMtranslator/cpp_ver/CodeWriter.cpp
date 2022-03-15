#include "CodeWriter.hpp"
#include "Parser.hpp"

MyClass::CodeWriter::CodeWriter(string vm_filename, VmCodeInfo vm_code_info)
    : vm_filename_{vm_filename}, vm_code_info_{vm_code_info}

//eq gt lt はまったく別の挙動をさせる label を使ってそこにjump させるようにする
//残項目は neg, eq, gt, lt
void MyClass::CodeWriter::WriteArithmetic(){
    string arithmetic = vm_code_info_.arg1;
    char ope = ArithmeticTable[arithmetic];
    /** サンプル
    * push 10
    * push 3
    * sub
    */
    printf("@SP");
    printf("A=M-1");
    printf("D=M"); //スタックから3を取得
    printf("@SP");
    printf("A=M-1");
    printf("D=M%cD", ope); //10 - 3
    printf("@SP");
    printf("A=M");
    printf("M=D"); //スタックに戻す
    printf("@SP");
    printf("M=M+1"); //スタックをインクリメント
}


void MyClass::CodeWriter::WritePushPop(){
    if (!(vm_code_info_.command_type == C_PUSH || vm_code_info_.command_type == C_POP)){ //push, pop 以外ならば
        printf("only push and pop are allowed!");
        return;
    }

    std::string reg = RegisterTable[vm_code_info_.arg1];
    int memory_location = vm_code_info_.arg2;
    if (vm_code_info_.command_type == C_PUSH){
        cout << "@" << reg << endl; //needs to be fixed
        printf("A=M+%d", memory_location); //needs to be fixed
        printf("D=M");  //値を取得
        printf("@SP");
        printf("A=M");
        printf("M=D");
        printf("@SP");
        printf("M=M+1");
    }else if (vm_code_info_.command_type == C_POP){
        printf("@SP");
        printf("M=M-1");
        printf("A=M");
        printf("D=M"); //stack をデクリメントして値を取得
        cout << "@" << reg << endl; //needs to be fixed
        printf("A=M+%d", memory_location);  //needs to be fixed
        printf("M=D");
    }

}
