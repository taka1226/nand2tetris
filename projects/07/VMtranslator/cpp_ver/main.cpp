#include <iostream>
#include "Parser.hpp"

int main(){
    Parser parser("./file/test.vm");

    do{
        parser.advance();
        VmCodeInfo vm = parser.parse();

    }
    while ( !parser.hasMoreLines() );


    return 0;
}
