struct FileManager {
  std::ifstream fin;
  std::ofstream fout;
  std::string line;
  std::string filePath;

  FileManager(std::string file_path){
    filePath = file_path;
  }


  fin.open();
}
