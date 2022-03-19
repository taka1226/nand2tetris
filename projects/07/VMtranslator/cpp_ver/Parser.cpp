#include "Parser.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace MyLibrary{
    // 空白で区切る
    std::vector<std::string> split(const std::string& src, const char* delim) {
        std::vector<std::string> vec;
        std::string::size_type len = src.length();

        for (std::string::size_type i = 0, n; i < len; i = n + 1) {
            n = src.find_first_of(delim, i);
            if (n == std::string::npos) {
                n = len;
            }
            vec.push_back(src.substr(i, n - i));
        }

        return vec;
    }

    //改行コードを取り除く
    void deleteNl2(std::string &targetStr)
    {
    	const char CR = '\r';
    	const char LF = '\n';
    	std::string destStr;
    	for (const auto c : targetStr) {
    		if (c != CR && c != LF) {
    			destStr += c;
    		}
    	}
    	targetStr = std::move(destStr);
    }
}

namespace MyClass {
    //ctor
    Parser::Parser(std::string vm_filename){
        vm_file_.open(vm_filename);
    }

    Parser::~Parser(){
        vm_file_.close();
    }

    bool Parser::hasMoreLines(){
        return vm_file_.eof();
    }


    void Parser::advance(){
        getline(vm_file_, line_);
    }


    void Parser::setLine(std::string line){
        line_ = line;
    }

    void Parser::parse(VmCodeInfo& vm_code_info){
        if (line_.substr(0, 2) == "//"){ //コメントのところはc_comment
            vm_code_info.command_type = C_COMMENT;
            return;
        }

        std::vector splited_vec = MyLibrary::split(line_);
        for (auto& word : splited_vec){
            MyLibrary::deleteNl2(word);
        }
        if (splited_vec.size() >= 4){
            std::cout << line_ << std::endl;
            printf("wrong command!\n");
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

        }else if (splited_vec.size() == 1){  //算術演算のとき
            vm_code_info.command_type = C_ARITHMETIC;
            vm_code_info.arg1 = splited_vec[0];
            vm_code_info.arg2 = -1;
        }
    }

}
