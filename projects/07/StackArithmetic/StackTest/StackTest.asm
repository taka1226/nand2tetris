
//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL1
D;JEQ
@SP
A=M
M=0
@LABEL2
0;JMP
(LABEL1)
    @SP
    A=M
    M=-1
(LABEL2)
    @SP
    M=M+1


//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL3
D;JEQ
@SP
A=M
M=0
@LABEL4
0;JMP
(LABEL3)
    @SP
    A=M
    M=-1
(LABEL4)
    @SP
    M=M+1


//push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL5
D;JEQ
@SP
A=M
M=0
@LABEL6
0;JMP
(LABEL5)
    @SP
    A=M
    M=-1
(LABEL6)
    @SP
    M=M+1


//push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL7
D;JLT
@SP
A=M
M=0
@LABEL8
0;JMP
(LABEL7)
    @SP
    A=M
    M=-1
(LABEL8)
    @SP
    M=M+1


//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL9
D;JLT
@SP
A=M
M=0
@LABEL10
0;JMP
(LABEL9)
    @SP
    A=M
    M=-1
(LABEL10)
    @SP
    M=M+1


//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL11
D;JLT
@SP
A=M
M=0
@LABEL12
0;JMP
(LABEL11)
    @SP
    A=M
    M=-1
(LABEL12)
    @SP
    M=M+1


//push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL13
D;JGT
@SP
A=M
M=0
@LABEL14
0;JMP
(LABEL13)
    @SP
    A=M
    M=-1
(LABEL14)
    @SP
    M=M+1


//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL15
D;JGT
@SP
A=M
M=0
@LABEL16
0;JMP
(LABEL15)
    @SP
    A=M
    M=-1
(LABEL16)
    @SP
    M=M+1


//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
@SP
A=M
D=M-D
@LABEL17
D;JGT
@SP
A=M
M=0
@LABEL18
0;JMP
(LABEL17)
    @SP
    A=M
    M=-1
(LABEL18)
    @SP
    M=M+1


//push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 53
@53
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M+D
@SP
A=M
M=D
@SP
M=M+1

//push constant 112
@112
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
M=-M
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M&D
@SP
M=M+1

//push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1

@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M|D
@SP
M=M+1

@SP
M=M-1
A=M
M=!M
@SP
M=M+1
