/*********************************************************
** 作者：陈彦桦，王正
** 创始时间：2014-09-28
** 描述：构建Trie树，用于大规模的字符串的搜索
*********************************************************/
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include "trie.h"

int main(int argc, char** argv)
{
	time_t start,end;
	start = clock();
    int findNum = 0;
    Node* root = (Node*)malloc(sizeof(Node));
    root->ch = NULL; root->child = NULL; root->nextsibling = NULL;

    //printf("Start to build trie.\n");
    if(!buildTree(root, argv[1]))
    {
        printf("Failed to build Trie.\n");
        return 0;
    }
    //printf("Build trie complete.\n");
    //printf("\nStart to search trie.\n");
	
    findNum = findMail(root, argv[2], argv[3]);
    //printf("%d is found.\n", findNum);
	end = clock();
    freeTree(root);

	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
