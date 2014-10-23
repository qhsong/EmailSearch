#include<memory.h>

#include "trie.h"

T getloc(char c,const char** mails,T r)
{
	T p=NULL;
	p=r;
	while(p!=NULL)
	{
		if(mails[p->loc][(int)p->begin]==c)
			return p;
		else
			p=p->brother;
	}
	return NULL;
}

int compare(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails)
{	
	char* tmp1=(char*)calloc(e1-b1+2,sizeof(char));
	char* tmp2=(char*)calloc(e2-b2+2,sizeof(char));
	memcpy(tmp1,mails[l1]+b1,e1-b1+1);
	memcpy(tmp2,mails[l2]+b2,e2-b2+1);

	if(strcmp(tmp2,tmp1)==0)
	{
		free(tmp1);
		free(tmp2);
		return 0;
	}
	else
	{
		free(tmp1);
		free(tmp2);
		return -1;
	}
}

int prefix(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails)
{
	int i=0;
	
	char* tmp1=(char*)calloc(e1-b1+2,sizeof(char));
	char* tmp2=(char*)calloc(e2-b2+2,sizeof(char));
	memcpy(tmp1,mails[l1]+b1,e1-b1+1);
	memcpy(tmp2,mails[l2]+b2,e2-b2+1);

	if(strlen(tmp1)<strlen(tmp2))
	{
		while(tmp2[i]==tmp1[i] && i<strlen(tmp1))
			i++;
		if(i==strlen(tmp1))
		{
			free(tmp1);
			free(tmp2);
			return 0;
		}
		else
		{
			free(tmp1);
			free(tmp2);
			return -1;
		}
	}
	else
	{
		free(tmp1);
		free(tmp2);
		return -1;
	}
}

int comPrefix(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails)
{
	int i=0;

	char* tmp1=(char*)calloc(e1-b1+2,sizeof(char));
	char* tmp2=(char*)calloc(e2-b2+2,sizeof(char));
	memcpy(tmp1,mails[l1]+b1,e1-b1+1);
	memcpy(tmp2,mails[l2]+b2,e2-b2+1);

	while(tmp1[i]==tmp2[i] && i<strlen(tmp1) && i<strlen(tmp2))
		i++;

	return i;
}

void trie_init(T* r)
{
	(*r)=(trieNode*)calloc(1,sizeof(trieNode));
	(*r)->loc=-1;
	(*r)->begin=-1;
	(*r)->end=-1;
}

int trie_add(int l,char b,char e,const char** mails,T* r)
{
	T p=NULL;
	int _prefix=0;

	if(!r)
		return false;
	if(!mails)
		return false;

	if(!(*r))
	{
		trie_init(r);
		(*r)->loc=l;
		(*r)->begin=b;
		(*r)->end=e;
		return true;
	}
	else if(mails[(*r)->loc][(int)(*r)->begin]!=mails[l][(int)b])
	{
		trie_add(l,b,e,mails,&((*r)->brother));
		return true;
	}
	else if(compare((*r)->loc,(*r)->begin,(*r)->end,l,b,e,mails)==0)
		return true;
	else if(prefix((*r)->loc,(*r)->begin,(*r)->end,l,b,e,mails)==0)
	{
		b=b+((*r)->end-(*r)->begin)+1;
		trie_add(l,(char)b,e,mails,&((*r)->son));
		return true;
	}
	else
	{
		p=(*r);
		_prefix=comPrefix((*r)->loc,(*r)->begin,(*r)->end,l,b,e,mails);
		b=b+_prefix;

		trie_init(r);
		(*r)->loc=p->loc;
		(*r)->begin=p->begin;
		(*r)->end=p->begin+(_prefix-1);

		p->begin=p->begin+_prefix;
		(*r)->son=p;
		(*r)->brother=p->brother;
		p->brother=NULL;

		trie_add(l,b,e,mails,&(p->brother));
		return true;
	}
}

int trie_lookup(char* s,const char** mails,T r)
{
	T pTrie=NULL;
	int f1;
	char f2;
	
	pTrie=getloc((*s),mails,r);
	if(!pTrie)
		return false;
	else
	{
		f1=0;
		while(f1<strlen(s))
		{
			if(!pTrie || ((pTrie->end-pTrie->begin+1)>strlen(s)))
					return false;

			f2=pTrie->begin;
			while(f2<=pTrie->end)
			{
				if(*(s+f1)!=mails[pTrie->loc][(int)f2])
					return false;
				else
				{
					f1++;
					f2++;
				}
			}
			pTrie=getloc(*(s+f1),mails,pTrie->son);
		}
		return true;
	}
}

void destroy(T* r)
{
	if(!((*r)->brother))
		destroy(&((*r)->brother));
	if(!((*r)->son))
		destroy(&((*r)->son));
	free(*r);
}

void trie_destroy(T* r,char** mails)
{
	int i;
	destroy(&((*r)->son));
	free(r);

	for(i=0;i<MAIL_POOL;i++)
		free(mails[i]);
	free(mails);
}

