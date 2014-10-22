#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*#include"bloom.h"*/
#include"trie.h"

int main(int argc, char **argv)
{
/*	FILE *fpStrpool = fopen(argv[1],"r");
	FILE *fpCheckedstr = fopen(argv[2],"r");
		//FILE *fpResult = fopen(strcat(argv[3],"_bloom.dat"),"w");
	FILE *fpResult2 = fopen(strcat(argv[3],"_trie.dat"),"w");
	if(argc != 4) {
		printf("USAGE: strfind strpool strcheck result!\n");
		return 0;
	}
*/	
	
	FILE *fpStrpool = fopen("strpool.dat","r");
	FILE *fpCheckedstr = fopen("checkedemail.dat","r");
	FILE *fpResult2 = fopen("result_trie.dat","w");
/*	FILE *fpResult = fopen("result_bloom.dat","w");*/
	if(fpStrpool == NULL || fpCheckedstr == NULL){
		printf("Input file not found!\n");
		return 0;
	}
/*	bloom(fpStrpool,fpCheckedstr,fpResult);	
	rewind(fpStrpool);
	rewind(fpCheckedstr);
*/
	trie(fpStrpool,fpCheckedstr,fpResult2);
	
	fclose(fpStrpool);
	fclose(fpCheckedstr);
	fclose(fpResult2);
	return 0;
}
