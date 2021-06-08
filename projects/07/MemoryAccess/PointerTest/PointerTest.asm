
//push constant 3030
@3030
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer THIS
@SP
M=M-1
A=M
D=M
@THIS
A=M
M=D

//push constant 3040
@3040
D=A
@SP
A=M
M=D
@SP
M=M+1

//pop pointer THAT
@SP
M=M-1
A=M
D=M
@THAT
A=M
M=D

//push constant 32
@32
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THIS 2
@THIS
D=M
@2
A=D+A
D=A
@addr
M=D
@SP
M=M-1
A=M
D=M
@addr
A=M
M=D

//push constant 46
@46
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 6
@THAT
D=M
@6
A=D+A
D=A
@addr
M=D
@SP
M=M-1
A=M
D=M
@addr
A=M
M=D

//push pointer THIS
@THIS
A=M
D=M
@SP
A=M
M=D
@SP
M=M+1

//push pointer THAT
@THAT
A=M
D=M
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

//push THIS 2
@THIS  //base addr
D=M
@2
A=D+A
D=M
@SP
A=M  //stack base addr
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

//push THAT 6
@THAT  //base addr
D=M
@6
A=D+A
D=M
@SP
A=M  //stack base addr
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
