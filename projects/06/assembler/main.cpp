#include <iostream>
#include <fstream> //handling input and output file
#include <string>
#include <map>
#include <iostream>
#include <fstream> //handling input and output file
#include "Parser.hpp"
#include "Code.hpp"
#include "SymbolHandler.hpp"
#include "LabelParser.hpp"
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

  SymbolHandler symbolHandler();
  //analyze label
  int lineNum = 0;
  while(true){
    fin >> std::ws;　//空行をskip
    getline(fin, lineContent);

    if (lineContent.substr(0, 2) == "//") continue;  //skip comment out part
    LabelParser labelParser(lineContent, lineNum);
    std::string labelName = labelParser.labelName;
    int addr = labelParser.addr;

    symbolHandler.addEntry(labelName, addr)//symbolHandlerに追加
    lineNum++;
  }
  fin.close();

  //analyze variable
  fin.open(argv[1]);
  while(true){
    fin >> std::ws;
    getline(fin, lineContent);

    if (lineContent[0] == '@'){
        int i = 1;
        std::string variableName = "";
        for (;;){
            variableName += lineContent[i];
            if (lineContent[i] == '\0') break;
            i++;
        }

        int variableNum = 16;
        if (!symbolHandler.contains(variableName)){  //tsymbolhandlerにキーが存在しなければ追加
            symbolHandler.addEntry(variableName, variableNum);
            variableNum++;
        }
    }
  }
  fin.close();

  fin.open(argv[1]);
  //translate assembler into machine language
  while(true){
    fin >> std::ws;
    getline(fin, lineContent);

    if (fin.fail()) break;
    if (lineContent.substr(0, 2) == "//") continue;  //skip comment out part

    Parser parse(lineContent);
    if (lineContent[0] == '@'){
      instructionType = "A"; //A instruction
      parse.aParse();
      if (!parse.check_int(parse.addr)){  //addrにラベル名が入って入ればアドレスに変換する
          parse.labelIntoAddr(parse.addr)
      }
    }else{
      instructionType = "C"; //C instruction
      parse.cParse();
    }

    Code code;

    std::cout << code.translate(parse) << std::endl;
  }
  fin.close();
  // Parser parse("D=D-M");
  // Code code;
  // std::cout << parse.comp << std::endl;


}
