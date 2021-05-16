struct SymbolHandler {
  std::map<std::string, int> SymbolTable;

  SymbolHandler(){
    SymbolTable["R0"] = 0;
    SymbolTable["R1"] = 1;
    SymbolTable["R2"] = 2;
    SymbolTable["R3"] = 3;
    SymbolTable["R4"] = 4;
    SymbolTable["R5"] = 5;
    SymbolTable["R6"] = 6;
    SymbolTable["R7"] = 7;
    SymbolTable["R8"] = 8;
    SymbolTable["R9"] = 9;
    SymbolTable["R10"] = 10;
    SymbolTable["R11"] = 11;
    SymbolTable["R12"] = 12;
    SymbolTable["R13"] = 13;
    SymbolTable["R14"] = 14;
    SymbolTable["R15"] = 15;
  }

  void addEntry(std::string key, int value){
    SymbolTable[key] = value;
  }

  boolean contains(){
      boolean isExist = (SymbolTable.count(key) > 0);
      return isExist;
  }

  int getAddress(std::string key){
    return SymbolTable[key];
  }
}
