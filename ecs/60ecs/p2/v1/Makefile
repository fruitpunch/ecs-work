#wenzhang; Zhang, Wen Xi

spantree: main.o network.o
	g++ -Wall -ansi -g -o3 -o spantree main.o network.o
main.o: main.cpp network.h
	g++ -Wall -ansi -g -c -o3 -o main.o main.cpp
network.o: network.cpp network.h
	g++ -Wall -ansi -g -c -o3 -o network.o network.cpp
clean:
	rm -f spantree.out *.o