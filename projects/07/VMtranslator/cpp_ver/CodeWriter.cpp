#include "CodeWriter.hpp"
#include "Parser.hpp"
#include <vector>
#include <iostream>
#include <map>

std::map<std::string, std::string> RegisterTable =
{
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"},
    {"temp", "TEMP"},
};

std::map<std::string, char> ArithmeticTable =
{
    {"add", '+'},
    {"sub", '-'},
    {"add", '&'},
    {"or", '|'},
    {"not", '!'}
};

std::map<std::string, std::string> cmpTable =
{
    {"eq", "JEQ"},
    {"lt", "JLT"},
    {"gt", "JGT"}
};

namespace MyClass {
    CodeWriter::CodeWriter(std::string vm_filename){
        std::vector<std::string> splited_vec = MyLibrary::split(vm_filename, (const char*)".");
        output_filename_ = splited_vec[0] + ".asm";
        label_num_ = 0;
    }

    void CodeWriter::Write(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type == C_ARITHMETIC){
            WriteArithmetic(vm_code_info);
        }else if (vm_code_info.command_type == C_POP || vm_code_info.command_type == C_PUSH){
            WritePushPop(vm_code_info);
        }
    }

    //eq gt lt はまったく別の挙動をさせる LABEL を使ってそこにjump させるようにする
    //残項目は neg
    void CodeWriter::WriteArithmetic(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_ARITHMETIC){
            printf("only arithmetic is allowed!");
            return;
        }

        std::string arithmetic = vm_code_info.arg1;
        if (arithmetic == "eq" || arithmetic == "lt" || arithmetic == "gt"){
            std::string cmp_com = cmpTable[arithmetic];
            /** サンプル
            * push 10
            * push 3
            * lt
            */
            printf("@SP\n");
            printf("A=M-1\n");
            printf("D=M\n"); //スタックから3を取得
            printf("@SP\n");
            printf("A=M-1\n");
            printf("D=M-D\n"); //スタックから10を取得, 10 - 3
            printf("@LABEL%d\n", label_num_);
            int jmp_true_label_num = label_num_;
            label_num_++;
            printf("D;JEQ\n");
            printf("@SP\n");
            printf("A=M\n");
            printf("M=0\n");
            printf("@LABEL%d\n", label_num_);
            int jmp_false_label_num = label_num_;
            label_num_++;
            std::cout << "0;" << cmp_com << std::endl;
            printf("(LABEL%d)\n", jmp_true_label_num);
            printf("  @SP\n");
            printf("  A=M\n");
            printf("  M=-1\n");
            printf("(LABEL%d)\n", jmp_false_label_num);
            printf("  @SP\n");
            printf("  M=M+1\n");
            return;
        }


        char ope = ArithmeticTable[arithmetic];
        /** サンプル
        * push 10
        * push 3
        * sub
        */
        if (arithmetic == "neg"){ //neg ならば -にするだけ
            printf("@SP\n");
            printf("A=M-1\n");
            printf("M=-M\n"); //マイナスにして入れるだけ
            return;
        }
        printf("@SP\n");
        printf("A=M-1\n");
        printf("D=M\n"); //スタックから3を取得
        printf("@SP\n");
        printf("A=M-1\n");
        printf("D=M%cD\n", ope); //10 - 3
        printf("@SP\n");
        printf("A=M\n");
        printf("M=D\n"); //スタックに戻す
        printf("@SP\n");
        printf("M=M+1\n"); //スタックをインクリメント

        return;
    }


    void CodeWriter::WritePushPop(VmCodeInfo vm_code_info){
        if (!(vm_code_info.command_type == C_PUSH || vm_code_info.command_type == C_POP)){ //push, pop 以外ならば
            printf("only push and pop are allowed!\n");
            return;
        }

        if (RegisterTable.find(vm_code_info.arg1) == RegisterTable.end()){ //見つからなければ
            std::cout << vm_code_info.arg1 << " is not implemented" << std::endl;
            return;
        }

        std::string reg = RegisterTable[vm_code_info.arg1];
        int memory_location = vm_code_info.arg2;
        if (vm_code_info.command_type == C_PUSH){
            std::cout << "@" << reg << std::endl; //needs to be fixed
            printf("A=M+%d\n", memory_location); //needs to be fixed
            printf("D=M\n");  //値を取得
            printf("@SP\n");
            printf("A=M\n");
            printf("M=D\n");
            printf("@SP\n");
            printf("M=M+1\n");
        }else if (vm_code_info.command_type == C_POP){
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
            printf("D=M\n"); //stack をデクリメントして値を取得
            std::cout << "@" << reg << std::endl; //needs to be fixed
            printf("A=M+%d\n", memory_location);  //needs to be fixed
            printf("M=D\n");
        }

    }

}
