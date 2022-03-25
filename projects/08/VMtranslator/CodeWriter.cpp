#include "CodeWriter.hpp"

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
        std::string output_filename = base_filename_ + ".asm";
        asm_file_.open(output_filename); //ファイルを開く
        label_num_ = 0;
    }

    CodeWriter::~CodeWriter(){
        asm_file_.close();
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
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M-1" << std::endl;
            asm_file_ << "A=M" << std::endl;
            asm_file_ << "D=M" << std::endl; //スタックから3を取得
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M-1" << std::endl;
            asm_file_ << "A=M" << std::endl;
            asm_file_ << "D=M-D" << std::endl; //スタックから10を取得, 10 - 3
            asm_file_ << "@LABEL" << label_num_ << std::endl;
            int jmp_true_label_num = label_num_;
            label_num_++;
            asm_file_ << "D;JEQ" << std::endl;
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "A=M" << std::endl;
            asm_file_ << "M=0" << std::endl;
            asm_file_ << "@LABEL" << label_num_ << std::endl;
            int jmp_false_label_num = label_num_;
            label_num_++;
            asm_file_ << "0;" << cmp_com << std::endl;
            asm_file_ << "(LABEL" << jmp_true_label_num << ")" << std::endl;
            asm_file_ << "  @SP" << std::endl;
            asm_file_ << "  A=M" << std::endl;
            asm_file_ << "  M=-1" << std::endl;
            asm_file_ << "(LABEL" << jmp_false_label_num << ")" << std::endl;
            asm_file_ << "  @SP" << std::endl;
            asm_file_ << "  M=M+1" << std::endl;
            return;
        }


        char ope = ArithmeticTable[arithmetic];
        /** サンプル
        * push 10
        * push 3
        * sub
        */
        if (arithmetic == "neg"){ //neg ならば -にするだけ
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M-1" << std::endl;
            asm_file_ << "A=M" << std::endl;
            asm_file_ << "M=-M" << std::endl; //マイナスにして入れるだけ
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M+1" << std::endl;
            return;
        }

        if (arithmetic == "not"){
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M-1" << std::endl;
            asm_file_ << "A=M" << std::endl;
            asm_file_ << "M=!M" << std::endl; //notにして入れるだけ
            asm_file_ << "@SP" << std::endl;
            asm_file_ << "M=M+1" << std::endl;
            return;
        }

        asm_file_ << "@SP" << std::endl;
        asm_file_ << "M=M-1" << std::endl;
        asm_file_ << "A=M" << std::endl;
        asm_file_ << "D=M" << std::endl; //スタックから3を取得
        asm_file_ << "@SP" << std::endl;
        asm_file_ << "M=M-1" << std::endl;
        asm_file_ << "A=M" << std::endl;
        asm_file_ << "D=M" << ope << "D" << std::endl; //10 - 3
        asm_file_ << "@SP" << std::endl;
        asm_file_ << "A=M" << std::endl;
        asm_file_ << "M=D" << std::endl; //スタックに戻す
        asm_file_ << "@SP" << std::endl;
        asm_file_ << "M=M+1" << std::endl; //スタックをインクリメント

        return;
    }


    void CodeWriter::WritePushPop(VmCodeInfo vm_code_info){
        if (!(vm_code_info.command_type == C_PUSH || vm_code_info.command_type == C_POP)){ //push, pop 以外ならば
            printf("only push and pop are allowed!");
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
                asm_file_ << "@" << vm_code_info.arg2 << std::endl;
                asm_file_ << "D=A" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M+1" << std::endl;
                return;

            }else if (vm_code_info.arg1 == "static"){
                asm_file_ << "@" << base_filename_ << "." << memory_location << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M+1" << std::endl;
                return;

            }else if (vm_code_info.arg1 == "pointer"){
                asm_file_ << "@" << reg << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M+1" << std::endl;
                return;

            }else{
                asm_file_ << "@" << reg << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@" << memory_location << std::endl;
                asm_file_ << "A=D+A" << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M+1" << std::endl;

                return;
            }


        }else if (vm_code_info.command_type == C_POP){
            if (vm_code_info.arg1 == "constant"){ //constant なら
                printf("pop is not allowed");
                return;
            }

            if (vm_code_info.arg1 == "static"){
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M-1" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@" << base_filename_ << "." << memory_location << std::endl;
                asm_file_ << "M=D" << std::endl;
                return;

            }else if (vm_code_info.arg1 == "pointer"){
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M-1" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@" << reg << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                return;

            }else{
                asm_file_ << "@" << reg << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@" << memory_location << std::endl;
                asm_file_ << "A=D+A" << std::endl;
                asm_file_ << "D=A" << std::endl;
                asm_file_ << "@addr" << std::endl;
                asm_file_ << "M=D" << std::endl;
                asm_file_ << "@SP" << std::endl;
                asm_file_ << "M=M-1" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "D=M" << std::endl;
                asm_file_ << "@addr" << std::endl;
                asm_file_ << "A=M" << std::endl;
                asm_file_ << "M=D" << std::endl;
                return;
            }
        }

    }

    void CodeWriter::WriteLabel(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_LABEL){
            printf("only label command is allowed!");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        asm_file_ << "(" << label_name <<")" << std::endl;
    }

    void CodeWriter::WriteGoto(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_GOTO){
            printf("only goto command is allowed");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        asm_file_ << "@" << label_name << std::endl;
        asm_file_ << "0;JMP" << std::endl;
    }

    void CodeWriter::WriteIf(VmCodeInfo vm_code_info){
        if (vm_code_info.command_type != C_IF){
            printf("only if command is allowed");
            return;
        }

        std::string label_name = vm_code_info.arg1;

        asm_file_ <<"@SP" << std::endl;
        asm_file_ <<"M=M-1" << std::endl;
        asm_file_ <<"A=M" << std::endl;
        asm_file_ <<"D=M" << std::endl;  //ここで Dに true, false を格納する
        asm_file_ << "@" << label_name << std::endl;
        asm_file_ <<"D;JMP" << std::endl;
    }

}
