all: strfind

strfind: clisttrie.o main.o bloom.o hash.o
	cc -o strfind -g -Wall -pedantic clisttrie.o main.o bloom.o hash.o

clisttrie.o: clisttrie.c clisttrie.h
	cc -o clisttrie.o -g -Wall -pedantic -ansi -c clisttrie.c
bloom:bloom.c bloom.h
	cc -o bloom.o -g -Wall -pedantic -ansi -c bloom.c
main.o: main.c clisttrie.h bloom.h
	cc -o main.o -g -Wall -pedantic -ansi -c main.c
hash.o:hash.c hash.h
	cc -o hash.o -g -Wall -pedantic -ansi -c hash.c
clean:
	rm *.o && rm strfind
