#include<limits.h>
#include<string.h>

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
	int i;
	p->size = 0;
	p->filter = (int *) malloc(BITSIZE);
	for(i=0 ; i< count ; i++) {
		p->filter[i] = 0;
	}

	/* Init the function point */

	func[0] = RSHash;
	func[1] = JSHash;
	func[2] = PJWHash;
	func[3] = ELFHash;
	func[4] = BKDRHash;
	func[5] = SDBMHash;
	func[6] = DJBHash;
	func[7] = DEKHash;
	func[8] = BPHash;
	func[9] = FNVHash;
	func[10] = APHash;

	return 0;
}

int bloom_destroy(BF **bfArray)
{
	return 0;
}

int bloom_add(BF **bfArray,char *str)
{
	BF *p = *bfArray;
	int len = strlen(str);
	int i;
	for(i = 0 ; i<FUNCNUM ; i++ ) {
		int temp = func[i](str,len);
		SETBIT(p->filter,temp);
	}
	return 0;
}

int bloom_check(BF **bfArray,char *str)
{
	BF *p = *bfArray;
	int len = strlen(str);
	int i;
	for(i= 0 ;i <FUNCNUM ;i++) {
		int temp = func[i](str,len);
		int result = GETBIT(p->filter,temp);
		if(result == 0) return 0;
	}
	return 1;
}

void bloom(FILE *pool,FILE *check,FILE *result) {
	BF *b=bloom_create();
	char line[BUFFERSIZE];
	while(fgets(line,BUFFERSIZE,pool)) {
		bloom_add(&b,line);
	}
	while(fgets(line,BUFFERSIZE,check)) {
		if(bloom_check(&b,line)){
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}

}
