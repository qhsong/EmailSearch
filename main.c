#include<stdio.h>
#include<string.h>

#include"bloom.h"

int main(int argc, char *argv)
{
	if(argc != 4) {
		printf("USAGE: strfind strpool strcheck result!\n");
		return 0;
	}
	FILE *fpStrpool = fopen(argv[1],"r");
	FILE *fpCheckedstr = fopen(argv[2],"r");
	FILE *fpResult = fopen(argv[3],"w");
	if(fpStrpool == NULL || fpCheckedstr == NULL){
		printf("Input file not found!\n");
		return 0;
	}
	bloom(fpStrpool,fpCheckedstr,fpResult);
	return 0;
}
