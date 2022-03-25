#include "MyLibrary.hpp"

namespace MyLibrary{
    // 空白で区切る
    std::vector<std::string> split(const std::string& src, const char* delim) {
        std::vector<std::string> vec;
        std::string::size_type len = src.length();

        for (std::string::size_type i = 0, n; i < len; i = n + 1) {
            n = src.find_first_of(delim, i);
            if (n == std::string::npos) {
                n = len;
            }
            vec.push_back(src.substr(i, n - i));
        }

        // "" を取り除く、「//」がでてくればそのあとはすべて無視
        std::vector<std::string> ans_vec;
        for (auto& ele : vec){
            deleteNl2(ele);
            if (ele == ""){
                continue;
            }else if (ele == "//"){
                break;
            }else{
                ans_vec.push_back(ele);
            }
        }
        return ans_vec;
    }

    //改行コードを取り除く
    //タブ文字を空白文字に置き換える
    void deleteNl2(std::string &targetStr)
    {
    	const char CR = '\r';
    	const char LF = '\n';
    	std::string destStr;
    	for (const auto c : targetStr) {
            if (c == '\t'){
                destStr += ' ';
            }else if (c != CR && c != LF) {
    			destStr += c;
    		}
    	}
    	targetStr = std::move(destStr);
    }
}
