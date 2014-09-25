#include<stdio.h>
#include<string.h>

#include"bloom.h"
/* #include"trie.h" */

int main(int argc, char **argv)
{
	FILE *fpStrpool = fopen(argv[1],"r");
	FILE *fpCheckedstr = fopen(argv[2],"r");
	FILE *fpResult = fopen(strcat(argv[3],"_bloom"),"w");
	FILE *fpResult2 = fopen(strcat(argv[3],"_trie"),"w");
	if(argc != 4) {
		printf("USAGE: strfind strpool strcheck result!\n");
		return 0;
	}
	if(fpStrpool == NULL || fpCheckedstr == NULL){
		printf("Input file not found!\n");
		return 0;
	}
	bloom(fpStrpool,fpCheckedstr,fpResult);
	/*trie(fpStrpool,fpChechedstr,fpResult2);*/
	return 0;
}
