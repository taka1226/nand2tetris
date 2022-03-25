CXXFLAGS += -g -std=c++17

%.o: %.cpp Makefile
	g++ $(CXXFLAGS) -c $< -o $@

main: main.o Parser.o CodeWriter.o MyLibrary.o Makefile
	g++ -std=c++17 -g -o main main.o Parser.o CodeWriter.o MyLibrary.o

clean:
	rm -rf *.o main

.PHONY: clean
