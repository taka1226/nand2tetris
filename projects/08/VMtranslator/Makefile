Parser.o: Parser.cpp
	g++ -std=c++17 -g -c Parser.o Parser.cpp

CodeWriter.o: CodeWriter.cpp
	g++ -std=c++17 -g -c CodeWriter.o CodeWriter.cpp

MyLibrary.o: MyLibrary.cpp
	g++ -std=c++17 -g -c MyLibrary.o MyLibrary.cpp

main.o: main.cpp
	g++ -std=c++17 -g -c main.o main.cpp

main: main.o Parser.o CodeWriter.o MyLibrary.o
	g++ -std=c++17 -g -o main main.o Parser.o CodeWriter.o MyLibrary.o

.PHONY: clean
clean:
	rm -rf *.o main
