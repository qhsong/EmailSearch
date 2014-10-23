all: strfind

strfind:main.o  trie.o
	cc -o strfind -Wall -pedantic main.o trie.o

main.o: main.c
	cc -o main.o -Wall -pedantic -c main.c

trie.o: trie.c trie.h
	cc -o trie.o -Wall -pedantic -c trie.c
