#include<limits.h>
#include<string.h>
	
#include "clisttrie.h"

#define BUFFERSIZE 1024

/*This function used to find the longest common header between s1 and s2.Return the max common character index,if not, return -1; */

int find_common_head(char *s1,char *s2) {
	int index = 0;
	while(*s1++==*s2++) index++;
	return index;
}

NODELIST* node_find(NODELIST *l,char *str,int *count) {
	while(l){
		if(*count = find_common_head(l->cNode,str)){
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
	char *pstr;
	while(*str){
		NODELIST *l =node_find(t->list,str,&index);
		if(l){	//exist the same header string.OK divided it.
			len1 = strlen(l->cNode);
			len2 = strlen(str);
			if(!l->tnext){
				l->tnext = (TRIE *)malloc(sizeof(TRIE));
				l->tnext->isEmail = false;
				l->tnext->list = NULL;
			}
			if(index == len2 && index !=len1){	//str is short
			
				//find the end of list
				TRIE *tp = l->tnext;
				NODELIST *p = tp->list,*q;
				q = p;
				while(p){
					q = p;
					p=p->next;
				}
				
				//new a sub node
				q->next = (NODELIST *)malloc(sizeof(NODELIST));
				q = q->next;
				pstr = l->cNode;
				pstr += index;
				strcpy(q->cNode,pstr);
				q->next = NULL;
				
				//change l->cNode
				l->cNode[index] = '\0';

				//if it is a word,then new a node
				if(tp->isEmail){
					q->tnext = (TRIE *)malloc(sizeof(TRIE));
					q->tnext->isEmail = true;
					q->tnext->list = NULL;
				}else{
					q->tnext = NULL;
				}
				
				//move t
				t = tp;
			}else if((index == len1 && index !=len2) ||(index ==len1 && index==len2)) {  //l->cNode
				t = l->tnext;
			}else{	//both has common parti,devided the nodelist
				NODELIST *p = l,*q;
				char *ps = str;
				q = p;
				while(p){
					q = p;
					p = p->next;
				}
				q->next = (NODELIST *)malloc(sizeof(TRIE));
				q = q->next;
				ps += index;
				strcpy(q->cNode,ps);
				q->tnext = l->tnext;
				l->cNode[index] = '\0';

			}
			str += index;
		}else{	//new
			NODELIST *p = t->list,*q;
			q = p;
			while(p) {
				q = p;
				p = p->next;
			}
			q->next = (NODELIST *)malloc(sizeof(NODELIST));
			q = q->next;
			strcpy(q->cNode,str);
			q->next = NULL;
			break;
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
