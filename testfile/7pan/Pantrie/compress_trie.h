#ifndef COMPRESS_TRIE_H_INCLUDED
#define COMPRESS_TRIE_H_INCLUDED

#include <string.h>
#include <stdlib.h>

#define getbit(a,i) (((a)>>(i))&(1))
#define setbit(a,i) (a) = ((a)|((1)<<(i)))
#define clearbit(a,i) (a) = ((a)&(~((1)<<(i))))

typedef struct TRIE_NODE
{
    char is_str;
    unsigned short num_of_bit;
    unsigned char* compress_of_bit;
    struct TRIE_NODE *point_of_zero,*point_of_one;
}trie_node;

//long int temp_of_new = 0;


void trie_node_init(trie_node **root);
int trie_insert(trie_node **root,char* bit_of_insert);
int trie_search(trie_node *root,char* bit_of_insert);
void trie_delete(trie_node *root);
void compress(trie_node *root,char* bit_of_insert);
int compare_of_bit(trie_node *root,char* bit_of_insert);
void pop_bit(trie_node *root,char* bit_of_pop,int len_of_pop);


#endif // COMPRESS_TRIE_H_INCLUDED
