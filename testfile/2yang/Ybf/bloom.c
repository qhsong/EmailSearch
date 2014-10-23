#include <limits.h>
#include <string.h>
#include <stdarg.h>

#include "bloom.h"

#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) ((a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))>>(n%CHAR_BIT))

BF* bloom_create(size_t htsize, size_t hfsize, ...)
{
	BF* bf;
	va_list l;
	int i;

	if(!(bf=(BF*)malloc(sizeof(BF))))
		return NULL;
	if(!(bf->hashTable=calloc((htsize+CHAR_BIT-1)/CHAR_BIT,sizeof(char))))
	{
		free(bf);
		return NULL;
	}
	if(!(bf->hf=(phashfunc*)malloc(hfsize*sizeof(phashfunc))))
	{
		free(bf->hashTable);
		free(bf);
		return NULL;
	}

	va_start(l,hfsize);
	for(i=0;i<hfsize;i++)
		bf->hf[i]=va_arg(l,phashfunc);
	va_end(l);

	bf->htsize=htsize;
	bf->hfsize=hfsize;

	return bf;
}

int bloom_destroy(BF* bf)
{
	free(bf->hashTable);
	free(bf->hf);
	free(bf);

	return 0;
}

int bloom_add(BF* bf,const char* mail)
{

	size_t i;

	for(i=0;i<bf->hfsize;i++)
		SETBIT(bf->hashTable,(bf->hf[i](mail,strlen(mail)))%bf->htsize);


	return 0;
}

int bloom_check(BF* bf,const char* mail)
{
	size_t i;
	unsigned int r=0;
	for(i=0;i<bf->hfsize;i++)
		r += GETBIT(bf->hashTable,bf->hf[i](mail,strlen(mail))%bf->htsize);
	return r;
}
