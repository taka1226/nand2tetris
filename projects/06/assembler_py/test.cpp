#include <iostream>
#include <fstream> //handling input and output file

int main(int argc, char *argv[]){
  std::ifstream fin;
  std::string line;

  fin.open(argv[1]);

  if(fin.fail()){
    std::cout << "fin.open() failed." << std::endl;
    return 9;

  }

  while(true){
    fin >> std::ws;
    getline(fin, line);
    if (fin.fail()) break;
    std::cout << line << std::endl;
    int i = 0;
    for (;;){
      if (line[i] == '\0') break;
      std::cout << line[i] << std::endl;
      i++;
    }

    break;
  }
  fin.close();
}
