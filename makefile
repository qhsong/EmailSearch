all: strfind

strfind: listtrie.o main.o
	cc -o strfind -g -Wall -pedantic listtrie.o main.o

listtrie.o: listtrie.c listtrie.h
	cc -o listtrie.o -g -Wall -pedantic -ansi -c listtrie.c

main.o: main.c trie.h
	cc -o main.o -g -Wall -pedantic -ansi -c main.c

clean:
	rm *.o && rm strfind
