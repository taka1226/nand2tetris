// #include <iostream>
// #include <fstream> //handling input and output file
// #include <string>
//hack アセンブリ言語を解析する
struct Parser {
  std::string lineContent;  //the content of one line
  std::string instructionType;
  std::string addr;
  std::string dest;
  std::string comp;
  std::string jump;

  Parser(std::string line){  //constructor
    lineContent = line;
    addr = "NULL";
    dest = "NULL";
    comp = "NULL";
    jump = "NULL";
  }

  void aParse(){
    if (instructionType == "C") return;
    addr = lineContent.substr(1);
  }

  void cParse(){
    int i = 0;
    int j = 0; //the number of dest end
    int lineEnd;
    for (;;){
      if (lineContent[i] == '\0'){
        lineEnd = i - 1;
        break;
      }
      i++;
    }
    i = 0;
    for (;;){
      // std::cout << i << " " << j <<  std::endl;
      if (lineContent[i] == '\0') break;
      if (lineContent[i] == '='){
        dest = lineContent.substr(0, i);
        comp = lineContent.substr(i + 1, lineEnd - i - 1);
        j = i + 1;
      }
      if (lineContent[i] == ';'){
        comp = lineContent.substr(j, i - j);
        jump = lineContent.substr(i + 1, lineEnd - i - 1);
      }
      i++;
    }
  }

  void labelIntoAddr(std::string labelName, SymbolHandler symbolHandler){
      addr_int = symbolHandler.getAddress();  //int type
      addr =  addr_int + '\0'; //change int type to string type
  }

  bool check_int(std::string str)　//文字列が数字かどうかをチェック
  {
      if (std::all_of(str.cbegin(), str.cend(), isdigit))
      {
          return true;
      }
      return false;
  }


};
