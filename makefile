all: strfind

strfind: listtrie.o main.o bloom.o hash.o
	cc -o strfind -g -Wall -pedantic listtrie.o main.o bloom.o hash.o

listtrie.o: listtrie.c listtrie.h
	cc -o listtrie.o -g -Wall -pedantic -ansi -c listtrie.c
bloom:bloom.c bloom.h
	cc -o bloom.o -g -Wall -pedantic -ansi -c bloom.c
main.o: main.c listtrie.h bloom.h
	cc -o main.o -g -Wall -pedantic -ansi -c main.c
hash.o:hash.c hash.h
	cc -o hash.o -g -Wall -pedantic -ansi -c hash.c
clean:
	rm *.o && rm strfind
