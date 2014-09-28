#include<limits.h>

#include "listtrie.h"

#define BUFFERSIZE 1024

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

NODELIST* node_find(NODELIST *l,char c) {
	while(l != null ){
		if( l->c == c) break;
		l = l->next;
	}
	return l;
}

TRIE* trie_create(){
	int i;
	TRIE *p = (TRIE *)malloc(sizeof(TRIE));
	p->isEmail = false;
	p->list = NULL;
	return p;
}

void trie_destroy(TRIE **head) {
	int i;
	free(*head);
}


int trie_add(TRIE **head,char *str) {
	TRIE *t = *head;
	while(str && *str != '\r' && *str !='\n'){
		NODELIST *l = node_find(l->list,*str);
		if(q){
			t = l->tnext;
		}else{
			NODELIST *p = t->list;
			NODELIST *q = p;
			while( p!= NULL) {
				q = p;
				p = p->next;
			}
			q->next = (NODELIST *)malloc(sizeof(NODELIST));
			q = q->next;
			q->c = *str;
			q->next = NULL;
			q->tnext = (TRIE *)malloc(sizeof(TRIE));
			t = q->tnext;
			t->list = NULL;
		}
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
