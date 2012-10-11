a.out : List.o ln.o test.o 
	g++ -ansi -Wall -g -c a.out List.o ln.o test.o 

List.o : List.cpp List.h ln.h 
	g++ -ansi -Wall -g -c List.cpp

ln.o : ln.cpp ln.h 
	g++ -ansi -Wall -g -c ln.cpp

test.o : test.cpp ln.h 
	g++ -ansi -Wall -g -c test.cpp

clean : 
	rm -f a.out List.o ln.o test.o 
