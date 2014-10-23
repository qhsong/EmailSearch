//
//  bloom.c
//  trie_compress
//
//  Created by 黄岁 on 14-10-23.
//  Copyright (c) 2014年 黄岁. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "bloom.h"
#include "hash.h"

#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

struct bloom *
bloom_init(unsigned int size,  phashfunc *funcs, unsigned int func_num)
{
    struct bloom *b;
    int i;
    
    if ((b = malloc(sizeof(struct bloom))) == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    b->str = malloc(size);
    if (b->str == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }
    
    if ((b->funcs = malloc(func_num * sizeof(funcs[0]))) == NULL) {
        fputs("malloc error\n", stderr);
        exit(1);
    }

    for (i = 0; i < func_num; ++i) {
        b->funcs[i] = funcs[i];
    }
    
    b->func_num = func_num;
    b->size = size;
    
    return b;
}

void
bloom_destroy(struct bloom *b)
{
    free(b->str);
    free(b->funcs);
    free(b);
}

void
bloom_insert(struct bloom *b, char *s)
{
    int i;
    if (!s) {
        return;
    }
    for (i = 0; i < b->func_num; ++i) {
        phashfunc f = b->funcs[i];
        unsigned int hash = (*f)(s, strlen(s)) % b->size;
        SETBIT(b->str, hash);
    }
}

int
bloom_search(struct bloom *b, char *s)
{
    int i;
    for (i = 0; i < b->func_num; ++i) {
        if (!(GETBIT(b->str, b->funcs[i](s, strlen(s)) % b->size)))
            return 0;
    }
    return 1;
}
