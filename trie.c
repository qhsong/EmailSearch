#include<limits.h>

#include "trie.h"

#define BUFFERSIZE 1024

/*int getpos(char a) {
	if(a>='a' && a<='z') {
		return a-97;
	}else if(a>='A' && a<='Z'){
		return a-65;
	}else if(a>='-' && a<='.') {
		return a-'-'+26;
	}else if(a>='0' && a<='9') {
		return a-'0'+28;
	}else if(a=='_') {
		return 38;
	}else if(a=='@') {
		return 39;
	}else{
		printf("unknown character:%c",a);
		exit(1);
	}
}
*/

int getpos(char a) {
	if(a>=' ' && a<='Z') {
		return a-32;
	}else if(a>='a' && a<='z') {
		return a-'a'+33;
	}else if(a>='[' && a<='_') {
		return a-'['+59;
	}else if(a == '{') {
		return 62;
	}else {
		printf("Unknown character:%c\n",a);
		exit(1);
	}
}

TRIE* trie_create(){
	int i;
	TRIE *p = (TRIE *)malloc(sizeof(TRIE));
	p->isEmail = false;
	for(i=0;i<40;i++) {
		p->next[i] = NULL;
	}
	return p;
}

void trie_destroy(TRIE **head) {
	int i;
	for(i=0;i<40;i++) {
		trie_destroy(&((*head)->next[i]));
	}
	free(*head);
}

int trie_add(TRIE **head,char *str) {
	TRIE *t = *head;
	int pos;
	while(str && *str != '\r' && *str !='\n'){
		pos = getpos(*str);
		if(!t->next[pos]){
			t->next[pos] = (TRIE *)malloc(sizeof(TRIE));
		}
		t = t->next[pos];
		str++;
	}
	t->isEmail = true;
	return 0;
}

int trie_check(TRIE **head,char *str) {
	TRIE *t = *head;
	int pos;
	while(t!=NULL && !t->isEmail && *str!='\r' && *str) {
		pos = getpos(*str);
		t = t->next[pos];
		str++;
	}

	if(t==NULL) {
		return 0;
	}else {
		return t->isEmail;
	} 

}

void trie(FILE *pool,FILE *check,FILE *result) {
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	int count=0;
	while(fgets(line,BUFFERSIZE,pool)) {
		trie_add(&head,line);
		printf("%d\n",++count);
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
