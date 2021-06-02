// #include <iostream>
// #include <fstream> //handling input and output file
// #include <string>
// #include <map>
// #include "Parser.cpp"

struct Code {
  //initialize tables
  std::map<std::string, std::string> tableDest;
  std::map<std::string, std::string> tableComp;
  std::map<std::string, std::string> tableJump;

  Code(){
    tableDest["NULL"] = "000";
    tableDest["M"] = "001";
    tableDest["D"] = "010";
    tableDest["MD"] = "011";
    tableDest["A"] = "100";
    tableDest["AM"] = "101";
    tableDest["AD"] = "110";
    tableDest["AMD"] = "111";

    tableComp["0"] = "0101010";
    tableComp["1"] = "0111111";
    tableComp["-1"] = "0111010";
    tableComp["D"] = "0001100";
    tableComp["A"] = "0110000";
    tableComp["!D"] = "0001101";
    tableComp["!A"] = "0110001";
    tableComp["-D"] = "0001111";
    tableComp["-A"] = "0110011";
    tableComp["D+1"] = "0011111";
    tableComp["A+1"] = "0110111";
    tableComp["D-1"] = "0001110";
    tableComp["A-1"] = "0110010";
    tableComp["D+A"] = "0000010";
    tableComp["D-A"] = "0010011";
    tableComp["A-D"] = "0000111";
    tableComp["D&A"] = "0000000";
    tableComp["D|A"] = "0010101";
    tableComp["M"] = "1110000";
    tableComp["!M"] = "1110001";
    tableComp["-M"] = "1110011";
    tableComp["M+1"] = "1110111";
    tableComp["M-1"] = "1110010";
    tableComp["D+M"] = "1000010";
    tableComp["D-M"] = "1010011";
    tableComp["M-D"] = "1000111";
    tableComp["D&M"] = "1000000";
    tableComp["D|M"] = "1010101";

    tableJump["NULL"] = "000";
    tableJump["JGT"] = "001";
    tableJump["JEQ"] = "010";
    tableJump["JGE"] = "011";
    tableJump["JLT"] = "100";
    tableJump["JNE"] = "101";
    tableJump["JLE"] = "110";
    tableJump["JMP"] = "111";

  }

  std::string translate(Parser parse){
    if (parse.instructionType == "A"){
      return aTypeTranslate(parse);
    }else if (parse.instructionType == "C"){
      return cTypeTranslate(parse);
    }else{
      return "NULL";
    }
  }

  std::string aTypeTranslate(Parser parse){
    std::string addr_str = parse.addr;
    int addr_decimal = atoi(addr_str.c_str());
    return toBinary(addr_decimal);
  }

  std::string cTypeTranslate(Parser parse){
    return "111" + tableComp[parse.comp] + tableDest[parse.dest] + tableJump[parse.jump];
  }

  std::string toBinary(int n)
  {
      std::string r;
      int i = 16;
      while (i > 0){
          r = ( n % 2 == 0 ? "0" : "1" ) + r;
          n /= 2;
          i--;
      }
      return r;
  }
};
