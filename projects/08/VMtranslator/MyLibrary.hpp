#include <vector>
#include <string>

namespace MyLibrary{
    std::vector<std::string> split(const std::string& src, const char* delim = " ");

    void deleteNl2(std::string &targetStr);
}
