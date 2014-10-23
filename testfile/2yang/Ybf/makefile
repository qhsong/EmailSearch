all: strsearch

strsearch: bloom.o main.o hash.o
	cc -o strsearch -Wall -s -O3 -pedantic bloom.o main.o hash.o

bloom.o: bloom.c bloom.h hash.h
	cc -o bloom.o -Wall -pedantic -ansi -c bloom.c

main.o: main.c bloom.h
	cc -o main.o -Wall -pedantic -ansi -c main.c

hash.o: hash.c hash.h
	cc -o hash.o -Wall -pedantic -ansi -c hash.c

clean:
	rm bloom.o main.o hash.o
