#include <fstream>
#include <string>
#include <iostream>

#include "../Parser.hpp"

using namespace std;

int main(){
    //string s = "./example.txt";
    //Parser parser(s);

    MyClass::Parser parser("./example.txt");
    parser.setLine("pop local 3 4");
    VmCodeInfo* s = parser.parse();

    cout << (s == nullptr) << endl;
    return 0;
}
