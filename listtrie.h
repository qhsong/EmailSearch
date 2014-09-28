#ifndef __LISTTRIE_H__
#define __LISTTRIE_H__

#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef struct sNodeList NODELIST;
typedef struct trieTree TRIE;

struct sNodeList {
	char c;
	TRIE *tnext;
	struct sNodeList *next;
};



struct trieTree{
	int isEmail;
	struct NODELIST *list;
};


TRIE* trie_create();
void trie_destroy(TRIE **head);
int trie_add(TRIE **head,char *str);
int trie_check(TRIE **head,char *str);
void trie(FILE *pool,FILE *check,FILE *result);

#endif
