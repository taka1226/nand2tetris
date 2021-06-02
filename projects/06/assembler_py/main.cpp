#include <iostream>
#include <fstream> //handling input and output file
#include <string>
#include <map>
#include <iostream>
#include <fstream> //handling input and output file
#include "Parser.hpp"
#include "Code.hpp"
// #include "FileManager.hpp"

int main(int argc, char *argv[]){
  std::ifstream fin;
  std::ofstream fout;
  std::string lineContent;

  fin.open(argv[1]);

  if(fin.fail()){
    std::cout << "fin.open() failed." << std::endl;
    return 9;
  }

  while(true){
    fin >> std::ws;
    getline(fin, lineContent);

    if (fin.fail()) break;
    if (lineContent.substr(0, 2) == "//") continue;

    Parser parse(lineContent);
    Code code;

    std::cout << code.translate(parse) << std::endl;
  }
  fin.close();

  // Parser parse("D=D-M");
  // Code code;
  // std::cout << parse.comp << std::endl;


}
