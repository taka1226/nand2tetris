#include "CodeWriter.hpp"
#include "Parser.hpp"
#include <vector>
#include <iostream>
#include <map>
#include <string>

std::map<std::string, std::string> RegisterTable =
{
    {"local", "LCL"},
    {"argument", "ARG"},
    {"this", "THIS"},
    {"that", "THAT"},
    {"temp", "R5"},
};

std::map<std::string, char> ArithmeticTable =
{
    {"add", '+'},
    {"sub", '-'},
    {"and", '&'},
    {"or", '|'},
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
        base_filename_ = splited_vec[0];
        output_filename_ = base_filename_ + ".asm";
        label_num_ = 0;
    }

    void CodeWriter::Write(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type == C_ARITHMETIC){
            WriteArithmetic(vm_code_info);
        }else if (vm_code_info.command_type == C_POP || vm_code_info.command_type == C_PUSH){
            WritePushPop(vm_code_info);
        }else if (vm_code_info.command_type == C_LABEL){
            WriteLabel(vm_code_info);
        }else if (vm_code_info.command_type == C_IF){
            WriteIf(vm_code_info);
        }else if (vm_code_info.command_type == C_GOTO){
            WriteGoto(vm_code_info);
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
            printf("M=M-1\n");
            printf("A=M\n");
            printf("D=M\n"); //スタックから3を取得
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
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
            printf("M=M-1\n");
            printf("A=M\n");
            printf("M=-M\n"); //マイナスにして入れるだけ
            printf("@SP\n");
            printf("M=M+1\n");
            return;
        }

        if (arithmetic == "not"){
            printf("@SP\n");
            printf("M=M-1\n");
            printf("A=M\n");
            printf("M=!M\n"); //notにして入れるだけ
            printf("@SP\n");
            printf("M=M+1\n");
            return;
        }

        printf("@SP\n");
        printf("M=M-1\n");
        printf("A=M\n");
        printf("D=M\n"); //スタックから3を取得
        printf("@SP\n");
        printf("M=M-1\n");
        printf("A=M\n");
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

        std::string reg;
        if (RegisterTable.find(vm_code_info.arg1) != RegisterTable.end()){
            reg = RegisterTable[vm_code_info.arg1];
        }

        if (vm_code_info.arg1 == "pointer"){ //pointer
            if (vm_code_info.arg2 == 0){
                reg = "THIS";
            }else if (vm_code_info.arg2 == 1){
                reg = "THAT";
            }
        }

        int memory_location = vm_code_info.arg2;
        if (vm_code_info.command_type == C_PUSH){
            if (vm_code_info.arg1 == "constant"){ //constant なら
                printf("@%d\n", vm_code_info.arg2);
                printf("D=A\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
                return;

            }else if (vm_code_info.arg1 == "static"){
                std::cout << "@" << base_filename_ << "." << memory_location << std::endl;
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
                return;

            }else if (vm_code_info.arg1 == "pointer"){
                std::cout << "@" << reg << std::endl;
                printf("A=M\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");
                return;

            }else{
                std::cout << "@" << reg << std::endl;
                printf("D=M\n");
                printf("@%d\n", memory_location);
                printf("A=D+A\n");
                printf("D=M\n");
                printf("@SP\n");
                printf("A=M\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M+1\n");

                return;
            }


        }else if (vm_code_info.command_type == C_POP){
            if (vm_code_info.arg1 == "constant"){ //constant なら
                printf("pop is not allowed\n");
                return;
            }

            if (vm_code_info.arg1 == "static"){
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                std::cout << "@" << base_filename_ << "." << memory_location << std::endl;
                printf("M=D\n");
                return;

            }else if (vm_code_info.arg1 == "pointer"){
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                std::cout << "@" << reg << std::endl;
                printf("A=M\n");
                printf("M=D\n");
                return;

            }else{
                std::cout << "@" << reg << std::endl;
                printf("D=M\n");
                printf("@%d\n", memory_location);
                printf("A=D+A\n");
                printf("D=A\n");
                printf("@addr\n");
                printf("M=D\n");
                printf("@SP\n");
                printf("M=M-1\n");
                printf("A=M\n");
                printf("D=M\n");
                printf("@addr\n");
                printf("A=M\n");
                printf("M=D\n");
                return;
            }
        }

    }

    void CodeWriter::WriteLabel(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_LABEL){
            printf("only label command is allowed!\n");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        std::cout << "(" << label_name <<")" << std::endl;
    }

    void CodeWriter::WriteGoto(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_GOTO){
            printf("only goto command is allowed\n");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        std::cout << "@" << label_name << std::endl;
        printf("0;JMP\n");
    }

    void CodeWriter::WriteIf(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_IF){
            printf("only if command is allowed\n");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        printf("@SP\n");
        printf("M=M-1\n");
        printf("A=M\n");
        printf("D=M\n");  //ここで Dに true, false を格納する
        std::cout << "@" << label_name << std::endl;
        printf("D;JMP\n");
    }

}
