/**
Author：AndrewPan,Sun
date：2014.10.13
summary：完成对(len_of_hufm+1)/2个字符的Huffman编码工作
*/

#include "huffman.h"

//当需要对x个字符进行编码时，需要开辟2x-1个hufm节点用于编码
void hufm_init(huffman_node hufm[],int len_of_hufm)
{
    int i;
    for(i=0;i<len_of_hufm;i++)
    {
        hufm[i].num_of_ch = 0;
        strcpy(hufm[i].code,"");
        hufm[i].left = -1;
        hufm[i].right = -1;
        hufm[i].flag = 0;
    }
}


void huffman_coding(huffman_node hufm[],int len_of_hufm)
{
    int mini,mini2;
    int pos_of_mini,pos_of_mini2;
    int i,j;
    for(i=(len_of_hufm+1)/2;i<len_of_hufm;i++)
    {
        mini = MAXNUM;
        mini2 = MAXNUM;
        pos_of_mini = -1;
        pos_of_mini2 = -1;
        for(j=0;j<i;j++)
        {
            if(!hufm[j].flag)
            {
                if(hufm[j].num_of_ch<mini)
                {
                    mini2 = mini;
                    pos_of_mini2 = pos_of_mini;
                    mini = hufm[j].num_of_ch;
                    pos_of_mini = j;
                }
                else if(hufm[j].num_of_ch<mini2)
                {
                    mini2 = hufm[j].num_of_ch;
                    pos_of_mini2 = j;
                }
            }
        }
        hufm[i].num_of_ch = mini + mini2;
        hufm[i].left = pos_of_mini;
        hufm[i].right = pos_of_mini2;
        hufm[pos_of_mini].flag = 1;
        hufm[pos_of_mini2].flag = 1;
    }

    char code[20];
    dfs(hufm,len_of_hufm-1,code,0);
}


void dfs(huffman_node hufm[],int root,char code[],int depth)
{
    int i;
    if(hufm[root].left==-1 && hufm[root].right==-1)
    {
        for(i=0;i<depth;i++)
        {
            hufm[root].code[i] = code[i];
        }
        hufm[root].code[depth] = '\0';
    }
    if(hufm[root].left!=-1)
    {
        code[depth] = '0';
        dfs(hufm,hufm[root].left,code,depth+1);
    }
    if(hufm[root].right!=-1)
    {
        code[depth] = '1';
        dfs(hufm,hufm[root].right,code,depth+1);
    }
}
