#ifndef __TRIE_H__
#define __TRIE_H__
#include <stdio.h>
#include <stdlib.h>
struct trie_node{
		struct trie_node *next[40];
		int n;
		};
typedef struct trie_node Trie;
void trieInsert(Trie *, const char *);
int trieSearch(Trie *, const char *);
void trieCheck(FILE *,FILE *,FILE *);
int charToIndex(char);
void initial(Trie *);
void trieDel(Trie *);
int checkstring(char *);

#endif