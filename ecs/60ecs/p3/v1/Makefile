#wenzhang; Zhang, Wen Xi

huffman.out: main.o tree.o
	g++ -Wall -ansi -g -o3 -o huffman.out main.o tree.o
main.o: main.cpp tree.h
	g++ -Wall -ansi -g -c -o3 -o main.o main.cpp
tree.o: tree.cpp tree.h
	g++ -Wall -ansi -g -c -o3 -o tree.o tree.cpp
clean:
	rm -f huffmanout *.o