#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__

#include <stdlib.h>
#include "hash.h"

#define HT_MAX_SIZE 239620000

typedef struct {
size_t htsize;
unsigned char* hashTable;
size_t hfsize;
phashfunc* hf;

}BF;

BF* bloom_create(size_t htsize, size_t hfsize, ...);
int bloom_destroy(BF* bf);
int bloom_add(BF* ,const char* mail);
int bloom_check(BF* bf ,const char* mail);

#endif
