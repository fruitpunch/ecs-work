#Hiu Hong Yu && Wen Xi Zhang
funix.out: permission.o directory.o funix.o main.o Time.o linkedlist.o
	g++ -Wall -ansi -g -o funix.out permission.o directory.o funix.o main.o Time.o linkedlist.o
main.o: main.cpp funix.h
	g++ -Wall -ansi -g -c main.cpp
funix.o: funix.cpp funix.h directory.h Time.h linkedlist.h
	g++ -Wall -ansi -g -c funix.cpp
directory.o: directory.cpp permission.h directory.h Time.h linkedlist.h
	g++ -Wall -ansi -g -c directory.cpp
permission.o: permission.cpp permission.h
	g++ -Wall -ansi -g -c permission.cpp
Time.o: Time.cpp Time.h
	g++ -Wall -ansi -g -c Time.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -Wall -ansi -g -c linkedlist.cpp

clean:
	rm -f funix.out permission.o directory.o main.o funix.o Time.o linkedlist.o
