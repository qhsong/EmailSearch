/*
 *
 * Decription:Find a email string in 10000000 emails string,if find printf yes ,or             print no.
 * Author:qhsong,cunwang
 * param:first is 1000000 input files,the second is the checked emails file,the last is result output
 *
 *
 *
 *
 * 
 * */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"trie.h"

int main(int argc, char **argv)
{
	FILE *fpStrpool = fopen(argv[1],"r");
	FILE *fpCheckedstr = fopen(argv[2],"r");
	FILE *fpResult2 = fopen(argv[3],"w");
	if(argc != 4) {
		printf("USAGE: strfind strpool strcheck result!\n");
		return 0;
	}
	
	if(fpStrpool == NULL || fpCheckedstr == NULL){
		printf("Input file not found!\n");
		return 0;
	}
	trie(fpStrpool,fpCheckedstr,fpResult2);
	
	fclose(fpStrpool);
	fclose(fpCheckedstr);
	fclose(fpResult2);
	return 0;
}
