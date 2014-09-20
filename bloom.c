#include<limits.h>

#include "bloom.h"
#include "hash.h"

#define BITSIZE 234881024
#define BUFFERSIZE 1024
#define FUNCNUM 11 
#define SETBIT(a, n) (a[n%(BITSIZE/sizeof(int))] |= (1<<(n%sizeof(int))))
#define GETBIT(a, n) (a[n/(BITSIZE/sizeof(int))] & (1<<(n%sizeof(int))))
phashfunc func[FUNCNUM];

BF* bloom_create()
{
	BF *p = (BF *)malloc(sizeof(BF));
	int count = BITSIZE / sizeof(int) ;
	p->size = 0;
	p->filter = (int *) malloc(BITSIZE);
	for(int i=0 ; i< count ; i++) {
		p->filter[i] = 0;
	}

	//init function array
	func[0] = RSHash;
	func[1] = JSHash;
	func[2] = PJWHash;
	func[3] = ELFHash;
	func[4] = 
}

int bloom_destroy(BF **bfArray)
{
	return 0;
}

int bloom_add(BF **bfArray,char *str)
{
	
}

int bloom_check()
{
	return 0;
}

void bloom(FILE *pool,FILE *check,FILE *result) {
	BF *b=bloom_create();
	char line[BUFFERSIZE];
	while(fgets(line,BUFFERSIZE,pool)) {
		bloom_add(&b,line);
	}

}
