#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include<stdlib.h>

typedef struct {
	unsigned int size;
	char *bf_vector;
/*other fields*/
}BF;

BF *bloom_create(char *filename, int vector_size);
int bloom_destroy(BF *bf);
int bloom_add(BF *bf, char *line);
int bloom_check(BF *bf, char *line);

#endif
