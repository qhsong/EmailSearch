/*
 * bloom.h
 *
 *  Created on: 2014-10-8
 *      Author: MaoBo
 */

#ifndef BLOOM_H_
#define BLOOM_H_
/*
 #ifndef __BLOOMFILTER_H__
 #define __BLOOMFILTER_H__
 */
#include<stdlib.h>

typedef struct {
	unsigned int size;
	char *hash_table;
} BF;

BF *bloom_create(int size);
int bloom_destroy(BF* bloomfilter);
int bloom_add(BF *bloomfilter, char *str);
int bloom_check(BF *bloomfilter, char *str);

/*
 #endif
 */

#endif /* BLOOM_H_ */
