#include <iostream>
#include <fstream> //handling input and output file
#include <string>
#include <map>
#include <iostream>
#include <fstream> //handling input and output file
#include <vector>
#include <algorithm>
#include <iostream>
#include "LabelParser.hpp"
#include "SymbolHandler.hpp"
#include "Parser.hpp"
#include "Code.hpp"
// #include "FileManager.hpp"



int main(int argc, char *argv[]){
  std::ifstream fin;
  std::ofstream fout;
  std::string lineContent;


  SymbolHandler symbolHandler;
  //analyze label
  fin.open(argv[1]);

  if(fin.fail()){
      std::cout << "fin.open() failed." << std::endl;
      return 9;
  }
  int lineNum = 0;
  while(true){
    fin >> std::ws;//空行をskip
    getline(fin, lineContent);
    if (fin.fail()) break;  //ファイルの終了
    if (lineContent.substr(0, 2) == "//") continue;  //skip comment out part
    LabelParser labelParser(lineContent, lineNum);
    std::string labelName = labelParser.labelName;
    int addr = labelParser.addr;
    if (labelParser.labelName != ""){
        symbolHandler.addEntry(labelName, addr); //symbolHandlerに追加
    }
    lineNum++;
  }
  fin.close();


  //analyze variable
  fin.open(argv[1]);
  while(true){
    fin >> std::ws;
    getline(fin, lineContent);
    lineContent.erase(remove(lineContent.begin(), lineContent.end(),' '), lineContent.end());
    if (fin.fail()) break;  //ファイルの終了
    if (lineContent[0] == '@'){
        int i = 1;
        int end_of_line;
        std::string variableName;
        for (;;){
            if (lineContent[i] == '\0'){
                end_of_line = i - 1;
                break;
            };
            i++;
        }
        variableName = lineContent.substr(1, end_of_line - 1);

        int variableNum = 16;

        if (!symbolHandler.contains(variableName)){  //tsymbolhandlerにキーが存在しなければ追加
            symbolHandler.addEntry(variableName, variableNum);
            variableNum++;
        }

    }
  }
  std::map<std::string, int> mp = symbolHandler.SymbolTable;
  auto begin = mp.begin(), end = mp.end();
  for (auto iter = begin; iter != end; iter++) {
      // first: key, second: value
      std::cout << "key = " << iter->first << "\n";
      std::cout << "value = " << iter->second << "\n";
  }
  fin.close();
  //
  fin.open(argv[1]);
  //translate assembler into machine language
  while(true){
    fin >> std::ws;
    getline(fin, lineContent);

    if (fin.fail()) break;
    if (lineContent.substr(0, 2) == "//") continue;  //skip comment out part
    lineContent.erase(remove(lineContent.begin(), lineContent.end(),' '), lineContent.end());

    Parser parse(lineContent);
    if (lineContent[0] == '@'){
      parse.instructionType = "A"; //A instruction
      parse.aParse();
      if (!parse.check_int(parse.addr)){  //addrにラベル名が入って入ればアドレスに変換する
          parse.labelIntoAddr(parse.addr, symbolHandler);
      }
    }else{
      parse.instructionType = "C"; //C instruction
      parse.cParse();
    }

    Code code;

    std::cout << code.translate(parse) << std::endl;
  }
  fin.close();
  Parser parse("D=D-M");
  Code code;
  std::cout << parse.comp << std::endl;


}
