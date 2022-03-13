#include "Parser.hpp"

MyClass::Parser::getVmCodeInfo(){
    //line_
    // quita 記事 正規表現 https://qiita.com/yohm/items/7c82693b83d4c055fa7b
    vm_code_info_ = m[0].str();
    vm_code_info_ = m[1].str();
    vm_code_info = m[2].str();
}
