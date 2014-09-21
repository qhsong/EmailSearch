all: strfind

strfind: bloom.o main.o hash.o trie.o
	cc -o strfind -g -Wall -pedantic bloom.o main.o hash.o trie.o

bloom.o: bloom.c bloom.h hash.h
	cc -o bloom.o -g -Wall -pedantic -ansi -c bloom.c

main.o: main.c bloom.h
	cc -o main.o -g -Wall -pedantic -ansi -c main.c

hash.o: hash.c hash.h
	cc -o hash.o -g -Wall -pedantic -ansi -c hash.c

