#include "Parser.hpp"

namespace MyClass {
    //ctor
    Parser::Parser(std::string vm_filename){
        vm_file_.open(vm_filename);
    }

    Parser::~Parser(){
        vm_file_.close();
    }

    bool Parser::hasMoreLines(){
        return !vm_file_.eof();
    }


    void Parser::advance(){
        getline(vm_file_, line_);
    }

    void Parser::parse(VmCodeInfo& vm_code_info){
        std::vector splited_vec = MyLibrary::split(line_);

        if (splited_vec.size() == 0){  //splited_vecの長さが0 skip_ を true に
            skip_ = true;
            return;
        }else{
            skip_ = false;
        }

        if (splited_vec.size() >= 4){
            printf("---------------------------------------------\n");
            std::cout << line_ << std::endl;
            printf("wrong command!\n");
            printf("---------------------------------------------\n");
            return;
        }
        if (splited_vec.size() == 3 && (splited_vec[0] == "push" || splited_vec[0] == "pop")){ //小文字のpush, pop だけ許可
            vm_code_info.arg1 = splited_vec[1]; //segment

            std::istringstream ss = std::istringstream(splited_vec[2]);
            ss >> vm_code_info.arg2;

            if (splited_vec[0] == "pop"){
                vm_code_info.command_type = C_POP;
            }else if (splited_vec[0] == "push"){
                vm_code_info.command_type = C_PUSH;
            }

        }else if (splited_vec.size() == 2){ //label command
            if (splited_vec[0] == "label"){
                vm_code_info.command_type = C_LABEL;
            }else if (splited_vec[0] == "if-goto"){
                vm_code_info.command_type = C_IF;
            }else if (splited_vec[0] == "goto"){
                vm_code_info.command_type = C_GOTO;
            }
            vm_code_info.arg1 = splited_vec[1];  //label の名前
            vm_code_info.arg2 = -1;

        }else if (splited_vec.size() == 1){  //算術演算のとき
            vm_code_info.command_type = C_ARITHMETIC;
            vm_code_info.arg1 = splited_vec[0];
            vm_code_info.arg2 = -1;
        }
    }

    bool Parser::isSkip(){
        return skip_;
    }

}
