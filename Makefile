all: main

main: main.o board.o view.o mask.o
	g++ main.o board.o view.o mask.o -o main

main.o: main.cxx board.hpp view.hpp types.hpp mask.hpp
	g++ -c main.cxx

board.o: board.cxx board.hpp types.hpp view.hpp
	g++ -c board.cxx

view.o: view.cxx view.hpp types.hpp board.hpp
	g++ -c view.cxx

mask.o: mask.cxx mask.hpp types.hpp
	g++ -c mask.cxx

clean:
	rm -f Fen.txt *.o main