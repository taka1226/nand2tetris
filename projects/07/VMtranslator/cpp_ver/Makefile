Parser.o: Parser.cpp
	g++ -std=c++17 -g -c Parser.o Parser.cpp

CodeWriter.o: CodeWriter.cpp
	g++ -std=c++17 -g -c CodeWriter.o CodeWriter.cpp

main.o: main.cpp
	g++ -std=c++17 -g -c main.o main.cpp

main: main.o Parser.o CodeWriter.o
	g++ -std=c++17 -g -o main main.o Parser.o CodeWriter.o

.PHONY: clean
clean:
	rm -rf *.o main
