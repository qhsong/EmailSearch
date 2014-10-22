all: strfind

strfind: clisttrie2.o main.o
	cc -o strfind -g -Wall -pedantic clisttrie2.o main.o

clisttrie2.o: clisttrie2.c clisttrie2.h
	cc -o clisttrie2.o -g -Wall -pedantic -ansi -c clisttrie2.c
main.o: main.c clisttrie2.h 
	cc -o main.o -g -Wall -pedantic -ansi -c main.c
clean:
	rm *.o && rm strfind
