#include<limits.h>

#include "trie.h"

#define BUFFERSIZE 1024

int getpos(char a) {
	if(a>='a' && a<='z') {
		return a-96;
	}else if(a>='-' && a<='.') {
		return a-'-'+27;
	}
}

TRIE* trie_create(){
	return (TRIE *)malloc(sizeof(TRIE));
}

int trie_detroy(BF **head) {
	return 0;
}

int trie_add(TRIE **head,char *str) {
	return 0;
}

int trie_check(TRIE **head,char *str) {
	return 0;
}

void trie(FILE *pool,FILE *check,FILE *result) {
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	while(fgets(line,BUFFERSIZE,pool)) {
		trie_add(&head,line);
	}
	while(fgets(line,BUFFERSIZE,check)) {
		if(trie_check(&head,line)) {
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}
}
