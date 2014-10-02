#include<limits.h>

#include "clisttrie.h"

#define BUFFERSIZE 1024

/*This function used to find the longest common header between s1 and s2.Return the max common character index,if not, return -1; */

int find_common_head(char *s1,char *s2) {
	int index = -1;
	while(*s1++==*s2++) index++;
	return index;
}

NODELIST* node_find(NODELIST *l,char c) {
}

TRIE* trie_create(){
	TRIE *head = (TRIE *)malloc(sizeof(TRIE));
	head->isEmail = false;
	head->list = NULL;
	return head;
}

void trie_destroy(TRIE **head) {
}


int trie_add(TRIE **head,char *str) {
}

int trie_check(TRIE **head,char *str) {

}

void trie(FILE *pool,FILE *check,FILE *result) {
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	int count=0;
	while(fgets(line,BUFFERSIZE,pool)) {
		trie_add(&head,line);
		if(!(++count%100000))	printf("%d\n",count);
/*		printf("%s",trie_check(&head,line)?"Yes":"No") ;*/
	}
	while(fgets(line,BUFFERSIZE,check)) {
		if(trie_check(&head,line)) {
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}
	trie_destroy(&head);
}
