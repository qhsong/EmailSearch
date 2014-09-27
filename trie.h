#ifndef __TRIE_H__
#define __TRIE_H__

#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0

struct trieTree{
	int isEmail;
	struct trieTree *next[63];
};

typedef struct trieTree TRIE;

TRIE* trie_create();
void trie_destroy(TRIE **head);
int trie_add(TRIE **head,char *str);
int trie_check(TRIE **head,char *str);
void trie(FILE *pool,FILE *check,FILE *result);

#endif
