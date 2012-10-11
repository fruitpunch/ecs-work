#Hiu Hong Yu && Wen Xi Zhang
funix.out: linkedlist.o Time.o permissions.o directory.o funix.o main.o
	g++ -Wall -ansi -g -o funix.out permissions.o directory.o funix.o main.o Time.o linkedlist.o
main.o: main.cpp funix.h
	g++ -Wall -ansi -g -c main.cpp
funix.o: funix.cpp funix.h directory.h
	g++ -Wall -ansi -g -c funix.cpp
directory.o: directory.cpp permissions.h directory.h Time.h linkedlist.h
	g++ -Wall -ansi -g -c directory.cpp
permissions.o: permissions.cpp permissions.h
	g++ -Wall -ansi -g -c permissions.cpp
Time.o: Time.cpp Time.h
	g++ -Wall -ansi -g -c Time.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -Wall -ansi -g -c linkedlist.cpp

clean:
	rm -f funix.out permissions.o directory.o main.o funix.o Time.o linkedlist.o
