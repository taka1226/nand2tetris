
//push constant 10
@10
D=A
@SP
A=M
M=D
@SP
M=M+1

// pop local 0
@local
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

// pop argument 2
@argument
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

// pop argument 1
@argument
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

// pop this 6
@this
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

// pop that 5
@that
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

// pop that 2
@that
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
@temp
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

//push local 0
@local  //base addr
D=M
@0
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1

//push that 5
@that  //base addr
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
M=M+1
A=M
M=D

//push argument 1
@argument  //base addr
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
A=M
D=M
@SP
M=M-1
A=M
M=M-D

//push this 6
@this  //base addr
D=M
@6
A=D+A
D=M
@SP
A=M  //stack base addr
M=D
@SP
M=M+1

//push this 6
@this  //base addr
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
M=M+1
A=M
M=D

@SP
A=M
D=M
@SP
M=M-1
A=M
M=M-D

//push temp 6
@temp  //base addr
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
M=M+1
A=M
M=D
