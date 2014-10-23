//
//  bloom.h
//  trie_compress
//
//  Created by 黄岁 on 14-10-23.
//  Copyright (c) 2014年 黄岁. All rights reserved.
//

#ifndef BLOOM_H
#define BLOOM_H

#include "hash.h"

struct bloom {
    unsigned int size;
    unsigned char *str;
    unsigned int func_num;
    phashfunc *funcs;
};

struct bloom *bloom_init(unsigned int size, phashfunc *funcs, unsigned int func_num);
void          bloom_destroy(struct bloom *b);
int           bloom_search(struct bloom *b, char *word);
void          bloom_insert(struct bloom *b, char *word);


#endif
