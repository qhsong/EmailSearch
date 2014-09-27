/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  A test file for strpool.dat
 *
 *        Version:  1.0
 *        Created:  2014年09月27日 16时24分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qhsong (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<string.h>

int getpos(char a) {
	if(a>='a' && a<='z') {
		return a-97;
	}else if(a>='A' && a<='Z'){
		return a-65;
	}else if(a>='-' && a<='.') {
		return a-'-'+26;
	}else if(a>='0' && a<='9') {
		return a-'0'+28;
	}else if(a=='_') {
		return 38;
	}else if(a=='@') {
		return 39;
	}else{
		return 41;
	}
}

int main() {
	FILE *in = fopen("strpool.dat","r");
	int count = 0;
	char line[1024];
	int len,i;
	while(fgets(line,1024,in)) {
		count++;
		len = strlen(line);
		for(i = 0; i< len - 2 ;i++){
			if(getpos(line[i])==41){
				printf("%d\n",count);
				break;
			}
		}
	}
	return 0;
}

