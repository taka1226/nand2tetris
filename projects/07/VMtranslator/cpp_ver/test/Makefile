Parser.o: ../Parser.cpp Makefile
	g++ -std=c++17 -g -c $@ $<

test.o: test.cpp Makefile
	g++ -std=c++17 -g -c $@ $<

test: Parser.o test.o Makefile
	g++ -std=c++17 -g -o $@ Parser.o test.o
