#Hiu Hong Yu && Wen Xi Zhang
funix.out: permission.o directory.o funix.o main.o Time.o
	g++ -Wall -ansi -g -o funix.out permission.o directory.o funix.o main.o Time.o
main.o: funix.h
	g++ -Wall -ansi -g -c main.cpp
funix.o: funix.h directory.h Time.h
	g++ -Wall -ansi -g -c funix.cpp
directory.o: permission.h directory.h Time.h
	g++ -Wall -ansi -g -c directory.cpp
permission.o: permission.h
	g++ -Wall -ansi -g -c permission.cpp
Time.o: Time.h
	g++ -Wall -ansi -g -c Time.cpp

clean:
	rm -f funix.out permission.o directory.o main.o funix.o Time.o
