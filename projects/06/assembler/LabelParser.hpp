struct LabelParser {
    std::string labelName;
    std::string lineContent;
    int addr;

    LabelParser(std::string line, int lineNum){
        lineContent = line;
        if (lineContent[0] == '('){
            addr = lineNum;
            getLabel();
        }
    }

    void getLabel(){
        int i = 1;
        labelName = "";
        for (;;){
            if (lineContent[i] != ')'){
                labelName += lineContent[i];
            }else{
                break;
            }
            i++;
        }

    }


};
