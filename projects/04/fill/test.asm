// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

// define variables
@16383
D = A
@screenStartAddr
M = D

@24574
D = A
@screenEndAddr
M = D

@24576
D = A
@keyboard
M = D

@LOOP
0;JMP

(LOOP)
  @keyboard
  A = M
  D = M   //detect keyboard's code

  @BLACK
  D;JGT    //jump to BLACK if keyboard's code is greater than  0

  @WHITE
  0;JMP


(BLACK)
  @screenStartAddr
  D = M
  @i
  M = D  //initialize i to screenStartAddr

  @LOOPBLACK
  0;JMP

  @LOOP
  0;JMP

(WHITE)
  @screenStartAddr
  D = M
  @i
  M = D  //initialize i to screenStartAddr

  @LOOPWHITE
  0;JMP

  @LOOP
  0;JMP

(LOOPBLACK)
  @i
  A = M
  M = -1  // make a part of screen black

  @i
  D = M   //take i value
  M = D + 1

  @screenEndAddr
  D = D - M
  @LOOPBLACK
  D;JLE

  @LOOP
  0;JMP

(LOOPWHITE)
  @i
  A = M
  M = 0  // make a part of screen white

  @i
  D = M   //take i value
  M = D + 1

  @screenEndAddr
  D = D - M
  @LOOPWHITE
  D;JLE

  @LOOP
  0;JMP
