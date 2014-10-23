#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <string.h>
#define MAXNUM 0x7fffffff

typedef struct HUFFMAN_MAN
{
    int num_of_ch;
    char code[20];
    int left,right;
    int flag;
}huffman_node;

void hufm_init(huffman_node hufm[],int len_of_hufm);
void huffman_coding(huffman_node hufm[],int len_of_hufm);
void dfs(huffman_node hufm[],int root,char code[],int depth);

#endif // HUFFMAN_H_INCLUDED
