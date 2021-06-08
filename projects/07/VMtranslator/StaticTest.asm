
//push constant 111
@111
D=A
@SP
M=D
A=A+1

//push constant 333
@333
D=A
@SP
M=D
A=A+1

//push constant 888
@888
D=A
@SP
M=D
A=A+1

//pop static 8
@SP
D=M
A=A-1
@StaticTest.8
M=D

//pop static 3
@SP
D=M
A=A-1
@StaticTest.3
M=D

//pop static 1
@SP
D=M
A=A-1
@StaticTest.1
M=D

//push static 3
@StaticTest.3
D=M
@SP
M=D
A=A+1

//push static 1
@StaticTest.1
D=M
@SP
M=D
A=A+1

@SP
D=M
A=A-1
M=M-D

//push static 8
@StaticTest.8
D=M
@SP
M=D
A=A+1

@SP
D=M
A=A-1
M=M+D
