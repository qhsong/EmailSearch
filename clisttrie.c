#include<limits.h>

#include "clisttrie.h"

#define BUFFERSIZE 1024

/*This function used to find the longest common header between s1 and s2.Return the max common character index,if not, return -1; */

int find_common_head(char *s1,char *s2) {
	int index = -1;
	while(*s1++==*s2++) index++;
	return index;
}

NODELIST* node_find(NODELIST *l,char *str,int *count) {
	while(l){
		if((*count = find_common_head(l->cNode,str))==-1){
			l = l->next;	
		}else{
			return l;
		}
	}
	return NULL;
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
	TRIE *t = *head;
	int index=0,len1,len2;
	char *temp;
	len2 = strlen(str);
	while(*str){
		NODELIST *l =node_find(t->list,str,&index);
		if(l){	//exist the same header string.OK divided it.
			len1 = strlen(l->cNode);
			if(index==len1 && index==len2){

			}else if(index == len2){
				if(!l->tnext){
					l->tnext = (TRIE *)malloc(sizeof(TRIE));
					l->tnext->list = NULL;
					l->tnext->isEmail = false;
				}
				t = l->tnext;
				str += index;
			}else if(index == len1) {
				temp = l->cNode;

			}else {
			
			}
		}else{	//new
			
		}
	}
}

int trie_check(TRIE **head,char *str) {

}

void trie(FILE *pool,FILE *check,FILE *result) {
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	int count=0;
	int i=0;
	while(fgets(line,BUFFERSIZE,pool)) {
		//delete the useless character '\r'
		i = 0;
		while(line[i++]!='\r');
		line[i] = '\0';

		trie_add(&head,line);
		if(!(++count%100000))	printf("%d\n",count);
/*		printf("%s",trie_check(&head,line)?"Yes":"No") ;*/
	}
	while(fgets(line,BUFFERSIZE,check)) {

		i = 0;
		while(line[i++]!='\r');
		line[i] = '\0';

		if(trie_check(&head,line)) {
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}
	trie_destroy(&head);
}
