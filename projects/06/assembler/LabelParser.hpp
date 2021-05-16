struct LabelParser {
    std::string labelName;
    int addr;

    LabelParser(std::string line, int lineNum){
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


}
