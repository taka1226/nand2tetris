
//push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop LCL 0
@LCL
D=M
@0
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

//push constant 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop ARG 2
@ARG
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

// pop ARG 1
@ARG
D=M
@1
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

//push constant 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THIS 6
@THIS
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

//push constant 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop THAT 5
@THAT
D=M
@5
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

// pop THAT 2
@THAT
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

//push constant 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop temp 6
@5
D=A
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

//push LCL 0
@LCL  //base addr
D=M
@0
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1

//push THAT 5
@THAT  //base addr
D=M
@5
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

//push ARG 1
@ARG  //base addr
D=M
@1
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

//push THIS 6
@THIS  //base addr
D=M
@6
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1

//push THIS 6
@THIS  //base addr
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

//push temp 6
@5  //base addr
D=A
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
