/*
 * trie.h
 *
 *  Created on: 2014-10-8
 *      Author: MaoBo
 */

#ifndef TRIE_H_
#define TRIE_H_

#ifndef __TRIE_H__
#define __TRIE_H__

#define NODE_SIZE 51
#define MAX_LENGTH 160

typedef struct trie_Node {
	int is_str;
	char *str;
	struct trie_Node** child;
} trie_Node;

void trie_add_node(char *str, trie_Node *root,trie_Node* father);
void trie_add(char *str, trie_Node *root);
int trie_check_node(char *str, trie_Node *root);
void trie_destroy(trie_Node *root);
void trie_destroy_node(trie_Node *root);
trie_Node* trie_create();
trie_Node* trie_new_Node(char* str);
int trie_check(char *str, trie_Node* root);
void run_trie(trie_Node* root,int deep);

#endif

#endif /* TRIE_H_ */
