#include <stdio.h>
#include <string.h>

#include "trie.h"
#include<time.h>

char* mails[MAIL_POOL];

char* reverse(char* mail)
{
	int i,length;
	char* m=NULL;
	length=strlen(mail);
	m=(char*)calloc(length+1,sizeof(char));

	for(i=0;i<length;i++)
		*(m+i)=*(mail+length-1-i);

	return m;
}

void trie(FILE* fp_srcpool,FILE* fp_chkpool,FILE* fp_result,T* r)
{
	char mail[150]={0};
	unsigned int i,count=0;

	while(fgets(mail,150,fp_srcpool))
	{
		mail[strlen(mail)-2]=0;
		if(strlen(mail)>126)
			continue;
		else
		{
			mails[count]=reverse(mail);
			count++;
			memset(mail,0,150);
		}
	}

	trie_init(r);
	for(i=0;i<count;i++)
	{
		if(trie_add(i,0,strlen(mails[i])-1,(const)mails,&((*r)->son))==0)
		{
			printf("adding error!\n");
			return;
		}
	}

	memset(mail,0,150);
	while(fgets(mail,150,fp_chkpool))
	{
		mail[strlen(mail)-2]=0;
		if(trie_lookup(reverse(mail),(const)mails,(*r)->son)==true)
			fprintf(fp_result,"%s    YES\n",mail);
		else
			fprintf(fp_result,"%s    NO\n",mail);

		memset(mail,0,150);
	}

	//printf("checking complete!\n");
	/*trie_destroy(r,mails);*/
}

int main(int argc, char *argv[])
{
	clock_t start=clock(),end;
	FILE* fp_srcpool;
	FILE* fp_chkpool;
	FILE* fp_result;
	T t=NULL;

	if(argc<4) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}

	fp_srcpool=fopen(argv[1],"r");
	fp_chkpool=fopen(argv[2],"r");
	fp_result=fopen(argv[3],"w");

	trie(fp_srcpool,fp_chkpool,fp_result,&t);

	fclose(fp_srcpool);
	fclose(fp_chkpool);
	fclose(fp_result);

	end = clock();
	printf("%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	//getchar();
	return 0;
}
