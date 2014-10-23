all: strsearch

strsearch: trie.o main.o
	cc -o strsearch -g -Wall -pedantic trie.o main.o

trie.o: trie.c trie.h
	cc -o trie.o -g -Wall -pedantic -ansi -c trie.c
main.o: main.c trie.h 
	cc -o main.o -g -Wall -pedantic -ansi -c main.c
clean:
	rm *.o && rm strfind
