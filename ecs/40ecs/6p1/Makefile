#Hiu Hong Yu && Wen Xi Zhang
funix.out: Time.o permissions.o file.o directory.o funix.o main.o
	g++ -Wall -ansi -g -o funix.out permissions.o directory.o funix.o main.o Time.o file.o
main.o: main.cpp funix.h
	g++ -Wall -ansi -g -c main.cpp
funix.o: funix.cpp funix.h directory.h
	g++ -Wall -ansi -g -c funix.cpp
directory.o: directory.cpp directory.h file.h
	g++ -Wall -ansi -g -c directory.cpp
permissions.o: permissions.cpp permissions.h
	g++ -Wall -ansi -g -c permissions.cpp
Time.o: Time.cpp Time.h
	g++ -Wall -ansi -g -c Time.cpp
file.o: file.cpp file.h Time.h permissions.h linkedlist.cpp linkedlist.h
	g++ -Wall -ansi -g -c file.cpp

clean:
	rm -f funix.out *.o
