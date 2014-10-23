#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true  1

#define MAIL_POOL 10032000

typedef struct Node
{
	int loc;
	char begin;
	char end;

	struct Node* brother;
	struct Node* son;
}trieNode,*T;

/*
 * c:input character
 *
 * return the location of string that start with the specific character
 */
T getloc(char c,const char** mails,T r);

/*
 * l1,b1,e1:string 1
 * l2,b2,e2:string 2
 *
 * if string1 equal the string2 return 0, else return -1
 *
 */
int compare(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails);

/*
 * l1,b1,e1:string 1
 * l2,b2,e2:string 2
 *
 * if string1 is the prefix of string2 return 0, else return -1
 *
 */
int prefix(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails);

/*
 * l1,b1,e1:string 1
 * l2,b2,e2:string 2
 *
 * return the length of common prefix between string1 and string2
 * if no common prefix return 0;
 */
int comPrefix(int l1,char b1,char e1,int l2,char b2,char e2,const char** mails);

void trie_init(T* r);

/*
 * l: the location of the new address in the matrix
 * mails: the matrix
 * r: point to the root of trie
 *
 *
 */
int trie_add(int l,char b,char e,const char** mails,T* r);
int trie_lookup(char* s,const char** mails,T r);
void destroy(T* r);
void trie_destroy(T* r,char** mails);

#endif
