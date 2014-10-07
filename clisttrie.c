#include<limits.h>
#include<string.h>
#include<time.h>
	
#include "clisttrie.h"

#define BUFFERSIZE 1024

/*This function used to find the longest common header between s1 and s2.Return the max common character index,if not, return -1; */

int find_common_head(char *s1,char *s2) {
	int index = 0;
	while(*s1!='\0' && *s2!='\0' && *s1++==*s2++) index++;
	return index;
}

NODELIST* node_find(NODELIST *l,char *str,int *count) {
	while(l){
		if((*count = find_common_head(l->cNode,str))== 0){
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
	NODELIST *p,*q;
	p = (*head)->list;
	while(p){
		trie_destroy(&(p->tnext));
		free(p->cNode);
		q = p;
		p = p->next;
		free(q);
	}
	free(*head);

}


int trie_add(TRIE **head,char *str) {
	TRIE *t = *head;
	int index=0,len1;
	char *pstr;
	while(*str){
		NODELIST *l =node_find(t->list,str,&index);
		if(l){	/*exist the same header string.OK divided it.*/
			len1 = strlen(l->cNode);
			if(index < len1){	/*str is short*/
			
				/*find the end of list*/
				TRIE *tp = l->tnext,*temp;
				NODELIST *q;
				temp =(TRIE *)malloc(sizeof(TRIE));
				
				/*new a sub node*/
				temp->isEmail = false;
				temp->list = (NODELIST *)malloc(sizeof(NODELIST));
				q = temp->list;
				pstr = l->cNode;
				pstr += index;
				q->cNode = (char *)malloc(4*strlen(pstr));
				strcpy(q->cNode,pstr);
				q->next = NULL;
				q->tnext = NULL;
				
				if(tp) {
					q->tnext = tp;		
				}
				
				/*redirect the node*/
				l->tnext = temp;

				/*change l->cNode*/
				l->cNode[index] = '\0';

				
				/*move t*/
				t = l->tnext;
			}else if(index == len1){  /*l->cNode is short*/
				if(!l->tnext){
					l->tnext = (TRIE *)malloc(sizeof(TRIE));
					l->tnext->isEmail = false;
					l->tnext->list = NULL;
				}
				t = l->tnext;
			}
		}else{	/*new*/
			NODELIST *p,*q;
			if(!t->list){
				t->list = (NODELIST *)malloc(sizeof(NODELIST));
				t->list->next = NULL;
				t->list->cNode = NULL;
				q = t->list;
			}else{
				q = p = t->list;
				while(p){
					q = p;
					p = p->next;
				}
				q->next = (NODELIST *)malloc(sizeof(NODELIST));
				q = q->next;
				q->cNode = NULL;
			}
			if(q->cNode){ 
				free(q->cNode);
				q->cNode = NULL;
			}
			q->cNode = (char *)malloc(4*strlen(str));
			strcpy(q->cNode,str);
			q->next = NULL;
			q->tnext = (TRIE *)malloc(sizeof(TRIE));
			q->tnext->isEmail = false;
			q->tnext->list = NULL;
			t = q->tnext;
			break;
		}
		str += index;
	}
	t->isEmail = true;
	return 0;
}

int trie_check(TRIE **head,char *str) {
	TRIE *t = *head;
	int index = 0;
	while(*str){
		NODELIST *l = node_find(t->list,str,&index);
		if(l && index == strlen(l->cNode)){
			t = l->tnext;	
			str += index;
		}else{
			t = NULL;
			break;
		}
	}
	if(t){
		return t->isEmail;
	}else{
		return false;
	}
}

void trie(FILE *pool,FILE *check,FILE *result) {
	clock_t start,end,start1;
	TRIE *head = trie_create();
	char line[BUFFERSIZE];
	int count=0;
	int i=0;
	start = clock();
	while(fgets(line,BUFFERSIZE,pool)) {
		/*delete the useless character '\r'*/
		i = 0;
		while(line[i]!='\r' && line[i]!='\n') i++;
		line[i] = '\0';

		trie_add(&head,line);
		if(!(++count%100000)){
			end = clock();
			printf("%d,%f \n",count,(double)(end -start)/CLOCKS_PER_SEC);
		}
/*		printf("%s",trie_check(&head,line)?"Yes":"No") ;*/
	}

	end = clock();
	printf("Creating tree using %f\n",(double)(end -start)/CLOCKS_PER_SEC);
	start1 = clock();
	while(fgets(line,BUFFERSIZE,check)) {

		i = 0;
		while(line[i]!='\r' && line[i]!='\n') i++;
		line[i] = '\0';

		if(trie_check(&head,line)) {
			fprintf(result,"yes\n");
		}else {
			fprintf(result,"no\n");
		}
	}
	end = clock();
	printf("Finding in %f\n",(double)(end -start1)/CLOCKS_PER_SEC);
	trie_destroy(&head);
}
