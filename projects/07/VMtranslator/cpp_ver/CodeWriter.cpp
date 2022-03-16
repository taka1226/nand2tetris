#include "CodeWriter.hpp"
#include "Parser.hpp"

MyClass::CodeWriter::CodeWriter(string vm_filename, VmCodeInfo vm_code_info)
    : vm_filename_{vm_filename}, vm_code_info_{vm_code_info}, label_num_{0};

//vm ファイルから新しいファイル名(asm) を作る
// void MyClass::CodeWriter::SetFileName(){
//
// }


//eq gt lt はまったく別の挙動をさせる LABEL を使ってそこにjump させるようにする
//残項目は neg, eq, gt, lt
void MyClass::CodeWriter::WriteArithmetic(){
    string arithmetic = vm_code_info_.arg1;
    if (arithmetic == "eq" || arithmetic == "lt" || arithmetic == "gt"){
        string cmp_com = cmpTable[arithmetic];
        /** サンプル
        * push 10
        * push 3
        * lt
        */
        printf("@SP");
        printf("A=M-1");
        printf("D=M"); //スタックから3を取得
        printf("@SP");
        printf("A=M-1");
        printf("D=M-D"); //スタックから10を取得, 10 - 3
        printf("@LABEL%d", label_num_);
        int jmp_true_label_num = label_num_;
        label_num_++;
        printf("D;JEQ")
        printf("@SP");
        printf("A=M");
        printf("M=0");
        printf("@LABEL%d", label_num_);
        int jmp_false_label_num = label_num_;
        label_num_++;
        cout << "0;" << cmp_com << endl;
        printf("(LABEL%d)", jmp_true_label_num);
        printf("  @SP");
        printf("  A=M");
        printf("  M=-1");
        printf("(LABEL%d)", jmp_falselabel_num);
        printf("  @SP");
        printf("  M=M+1");
        return;
    }


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

    return;
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
