all: strfind

strfind: bloom.o main.o hash.o 
	cc -o strfind -Wall -pedantic bloom.o main.o hash.o -std=c99

bloom.o: bloom.c bloom.h hash.h
	cc -o bloom.o -Wall -pedantic -ansi -c bloom.c -std=c99

main.o: main.c bloom.h
	cc -o main.o -Wall -pedantic -ansi -c main.c -std=c99

hash.o: hash.c hash.h
	cc -o hash.o -Wall -pedantic -ansi -c hash.c -std=c99

clean:
	-rm strfind bloom.o main.o hash.o
