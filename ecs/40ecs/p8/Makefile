#include Wen Xi Zhang & Yu Hiu Hong
all: p8.out p8b.out

p8.out: SVector.cpp SVector.h main.cpp
	g++ -Wall -ansi -g -DNDEBUG main.cpp -o p8.out

p8b.out: SVector.cpp SVector.h main.cpp
	g++ -Wall -ansi -g main.cpp -o p8b.out

clean:
	rm -f *.out *.o