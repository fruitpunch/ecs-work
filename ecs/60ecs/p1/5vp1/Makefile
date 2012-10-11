#wenzhang; Zhang, Wen Xi
sudsolve: main.o puzzle.o holder.o cell.o
	g++ -Wall -ansi -g -o sudsolve main.o puzzle.o holder.o cell.o
main.o: main.cpp puzzle.h
	g++ -Wall -ansi -g -c main.cpp
puzzle.o: puzzle.cpp puzzle.h holder.h
	g++ -Wall -ansi -g -c puzzle.cpp
holder.o: holder.cpp holder.h cell.h
	g++ -Wall -ansi -g -c holder.cpp
cell.o: cell.cpp cell.h
	g++ -Wall -ansi -g -c cell.cpp

clean:
	rm -f sudsolve *.o