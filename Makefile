all: main

main: main.o board.o view.o mask.o game.o historique.o
	g++ main.o board.o view.o mask.o game.o historique.o -o main

main.o: main.cxx board.hpp view.hpp types.hpp mask.hpp game.hpp
	g++ -c main.cxx

board.o: board.cxx board.hpp types.hpp view.hpp
	g++ -c board.cxx

view.o: view.cxx view.hpp types.hpp board.hpp
	g++ -c view.cxx

mask.o: mask.cxx mask.hpp types.hpp
	g++ -c mask.cxx

game.o: game.cxx game.hpp board.hpp mask.hpp view.hpp types.hpp historique.hpp
	g++ -c game.cxx

historique.o: historique.cpp historique.hpp types.hpp board.hpp view.hpp
	g++ -c historique.cpp

clean:
	rm -f Fen.txt historique.txt *.o main