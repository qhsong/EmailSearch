#ifndef __TRIE_H__
#define __TRIE_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	TRIE *next[40];
}TRIE;

TRIE* trie_create();
int trie_detroy(BF **head);
int trie_add(TRIE **head,char *str);
int trie_check(TRIE **head,char *str);
void trie(FILE *pool,FILE *check,FILE *result);

#endif
