all: main

main: main.o board.o view.o
	g++ main.o board.o view.o -o main

main.o: main.cxx board.hpp view.hpp types.hpp
	g++ -c main.cxx

board.o: board.cxx board.hpp types.hpp
	g++ -c board.cxx

view.o: view.cxx view.hpp types.hpp
	g++ -c view.cxx

clean:
	rm -f *.o main