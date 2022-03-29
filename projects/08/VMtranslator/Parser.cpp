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

    bool Parser::isSkip(){
        return skip_;
    }


    void Parser::parse(VmCodeInfo& vm_code_info){
        std::vector splited_vec = MyLibrary::split(line_);

        if (splited_vec.size() == 0){  //splited_vecの長さが0 skip_ を true に
            skip_ = true;
            return;
        }

        skip_ = false;

        if (splited_vec.size() >= 4){
            printf("---------------------------------------------\n");
            std::cout << line_ << std::endl;
            printf("wrong command!\n");
            printf("---------------------------------------------\n");
            return;
        }

        std::string cmd = splited_vec[0];
        if (cmd == "pop"){
            vm_code_info.command_type = C_POP;
            vm_code_info.arg1 = splited_vec[1]; //segment
            std::istringstream ss = std::istringstream(splited_vec[2]);
            ss >> vm_code_info.arg2;
            return;
        }
        if (cmd == "push"){
            vm_code_info.command_type = C_PUSH;
            vm_code_info.arg1 = splited_vec[1]; //segment
            std::istringstream ss = std::istringstream(splited_vec[2]);
            ss >> vm_code_info.arg2;
            return;
        }
        if (cmd == "label"){
            vm_code_info.command_type = C_LABEL;
            vm_code_info.arg1 = splited_vec[1];  //label の名前
            vm_code_info.arg2 = -1;
            return;
        }
        if (cmd == "if-goto"){
            vm_code_info.command_type = C_IF;
            vm_code_info.arg1 = splited_vec[1];  //label の名前
            vm_code_info.arg2 = -1;
            return;
        }
        if (cmd == "goto"){
            vm_code_info.command_type = C_GOTO;
            vm_code_info.arg1 = splited_vec[1];  //label の名前
            vm_code_info.arg2 = -1;
            return;
        }
        if (cmd == "add" || cmd == "sub" || cmd == "neg" || cmd == "eq" || cmd == "gt" || cmd == "lt" || cmd == "and" || cmd == "or" || cmd == "not"){
            vm_code_info.command_type = C_ARITHMETIC;
            vm_code_info.arg1 = cmd;
            vm_code_info.arg2 = -1;
            return;
        }
        if (cmd == "function"){
            vm_code_info.command_type = C_FUNCTION;
            vm_code_info.arg1 = splited_vec[1]; //function name
            std::istringstream ss = std::istringstream(splited_vec[2]);
            ss >> vm_code_info.arg2;
        }
        if (cmd == "call"){
            vm_code_info.command_type = C_CALL;
            vm_code_info.arg1 = splited_vec[1];  //function name
            std::istringstream ss = std::istringstream(splited_vec[2]);
            ss >> vm_code_info.arg2;
        }
        if (cmd == "return"){
            vm_code_info.command_type = C_RETURN;
            vm_code_info.arg1 = "return";
            vm_code_info.arg2 = -1;
        }

    }
}
