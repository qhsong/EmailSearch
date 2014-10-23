/**
	Author：AndrewPan,Sun
	date：2014.10.13~2014.10.15
	summary：程序主要完成海量字符串的查找工作。采用Huffman+压缩trie树的方法。
			首先对字符进行Huffman编码，将原始字符串转换为0、1比特串，
			然后将比特串插入压缩trie树中，最后在压缩trie树中判断需要查找的字符串是否存在。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "compress_trie.h"
#include <time.h>

#define NUM_OF_HUFFMAN 81
#define LENGTH_OF_LINE 10000
#define RESULT_OF_HUFFMAN "result_of_HUFFMAN.dat"
//#define EMAIL "strpool.dat"
//#define CHECKED_EMAIL "checkedemail.dat"
#define RESULT "result.dat"

void str_to_bin(char buf[],char binary[],huffman_node hufm[]);


int main(int argc, char *argv[])
{
    //time_t time_start,time_end;
    //time_start = time(NULL);
    clock_t start=clock(),end;
    char* EMAIL = argv[1];
    char* CHECKED_EMAIL = argv[2];

    huffman_node hufm[NUM_OF_HUFFMAN];
    hufm_init(hufm,NUM_OF_HUFFMAN);
    char buf[LENGTH_OF_LINE];
    char binary[LENGTH_OF_LINE];

    FILE* fin_of_huffman;
    fin_of_huffman = fopen(RESULT_OF_HUFFMAN,"r");
    if(fin_of_huffman == NULL)
    {
        hufm_init(hufm,NUM_OF_HUFFMAN);
        int i;
        for(i=0;i<(NUM_OF_HUFFMAN+1)/2;i++)
        {
            hufm[i].num_of_ch = NUM_OF_HUFFMAN - i;
        }
        huffman_coding(hufm,NUM_OF_HUFFMAN);
    }
    else
    {
        char temp_char;
        int i;
        for(i=0;i<(NUM_OF_HUFFMAN+1)/2;i++)
        {
            fgets(buf,sizeof(buf),fin_of_huffman);
            sscanf(buf,"%c %d %s",&temp_char,&hufm[i].num_of_ch,hufm[i].code);
        }
    }
    close(fin_of_huffman);

    //printf("building trie...");
    FILE* fin_of_email;
    fin_of_email = fopen(EMAIL,"r");
    trie_node *root;
    root = (trie_node*)malloc(sizeof(trie_node));
    trie_node_init(&root);

    while(fgets(buf,sizeof(buf),fin_of_email)!=NULL)
    {
        str_to_bin(buf,binary,hufm);
        trie_insert(&root,binary);
    }
    close(fin_of_email);
    //printf("\r");
    //printf("build trie success.\n");

    FILE *fin_of_checked,*fout_of_result;
    fin_of_checked = fopen(CHECKED_EMAIL,"r");
    fout_of_result = fopen(RESULT,"w");
    int num_yes = 0;
    int num_no = 0;
    while(fgets(buf,sizeof(buf),fin_of_checked)!=NULL)
    {
        str_to_bin(buf,binary,hufm);
        if(trie_search(root,binary))
        {
            fprintf(fout_of_result,"YES\n");
            num_yes++;
        }
        else
        {
            fprintf(fout_of_result,"NO\n");
            num_no++;
        }
    }
    //fprintf(fout_of_result,"num of YES is:%d\n",num_yes);
    //fprintf(fout_of_result,"num of NO is:%d\n",num_no);
    //printf("search success!\n");
    close(fin_of_checked);
    close(fout_of_result);
    //time_end = time(NULL);
	//printf("用时：%.0lfs\n", difftime(time_end, time_start));
    printf("%f\n",(double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}


void str_to_bin(char buf[],char binary[],huffman_node hufm[])
{
    int i;
    binary[0] = '\0';
    for(i=strlen(buf)-1;i>=0;i--)
    {
        if(buf[i]>='a' && buf[i]<='z')
        {
            strcat(binary,hufm[buf[i]-'a'].code);
        }
        else if(buf[i]>='A' && buf[i]<='Z')
        {
            strcat(binary,hufm[buf[i]-'A'].code);
        }
        else if(buf[i]>='0' && buf[i]<='9')
        {
            strcat(binary,hufm[26+buf[i]-'0'].code);
        }
        else if(buf[i]=='_')
        {
            strcat(binary,hufm[36].code);
        }
        else if(buf[i]=='-')
        {
            strcat(binary,hufm[37].code);
        }
        else if(buf[i]=='.')
        {
            strcat(binary,hufm[38].code);
        }
        else if(buf[i]=='@')
        {
            strcat(binary,hufm[39].code);
        }
        else
        {
            strcat(binary,hufm[40].code);
        }
    }
}
