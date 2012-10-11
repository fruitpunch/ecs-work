#Wen Xi Zhang && Hiu Hong Yu
songs.out: song.o main.o
	g++ -Wall -ansi -g -o songs.out song.o main.o
main.o: main.cpp song.h
	g++ -Wall -ansi -g -c main.cpp
song.o: song.cpp song.h
	g++ -Wall -ansi -g -c song.cpp

clean:
	rm -f songs.out song.o main.o