#include<limits.h>
//#include "trie.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_EMAIL_LENGTH 321
#define MAX_NEXT 62
#define MAX_CHAR_ASCII 123

FILE *fp = NULL;
char email[MAX_EMAIL_LENGTH];
int charTran[MAX_CHAR_ASCII+1];
int lineNum = 1;
int fileEnd = -1;

typedef struct trieNode
{
	int result; 
	struct trieNode *next[MAX_NEXT];
}trieNode;
trieNode *root = NULL;


int char_transfer()
{
	FILE *fp2 = NULL;
	char aChar;
	int i=0;
	if((fp2=fopen("ch.txt","r"))!=NULL)
	{
		while((aChar=fgetc(fp2))!= EOF)
		{
			charTran[aChar]=i;
			//printf("\n%d",charTran[aChar]);
			i++;
		}
		printf("\nChar ASCII transfer complete");
	}
	else
	{
		printf("\nOpen ch.txt error");
	    exit(1);
	}
	fclose(fp2);
}

void initial()
{	
    int i=0; 
	root=(trieNode*)malloc(sizeof(trieNode));
	for(i=0; i<MAX_NEXT; i++)
	{
		root->next[i]=NULL;
	}
	root->result=-1; 
}


trieNode* creat_node()
{
   int i=0;
   trieNode *p=(trieNode*)malloc(sizeof(trieNode));
   for(i=0; i<MAX_NEXT; i++)
	{
		p->next[i]=NULL;
	}
	p->result=-1;
	return p;
}


void insert()
{
  //trieNode *p = root;
//	printf("-----root's result is %d",p->result);
//	int j=charTran[email[0]];
//	p=p->next[j];
	int i=0;
	trieNode *p = root;
	for(i=0; i<MAX_EMAIL_LENGTH; i++)
	{
      //printf("\n------j is %d -------",j);
	  if((p->next[charTran[email[i]]]) == NULL)
	  {
	  	p->next[charTran[email[i]]]=creat_node();
  	  }	
 
  	  p = p->next[charTran[email[i]]];
  	  
  	  if(email[i+1]=='\n' || email[i+1]=='\0')
      {
      	p->result=1;
      	break;
      }
      
	}
}


int trie_check()
{
	int i=0;
	trieNode *p=root;
	for(i=0; i<MAX_EMAIL_LENGTH; i++)
	{
		
		if((p->next[charTran[email[i]]]) == NULL)
		    return -1;
        else
        {
        	p = p->next[charTran[email[i]]];
        	if(email[i+1]=='\n' || email[i+1]=='\0')
		  {
			if(p->result < 0)
			  return -1;
	        else
	          return 1;
		  }
        }      
		
	}
}

void file_open(char *fileName)
{
	
	if((fp=fopen(fileName,"r"))==NULL)
	{
		printf("\n%s was not successfully opened",fileName);
		exit(1);
	}
	else
	{
		printf("\n%s was opened successfully for read",fileName);
	}
} 

int read_line()
{
	int i;
    memset(email,0,sizeof(email));
	if(fgets(email,MAX_EMAIL_LENGTH,fp)!= NULL)
	{
		for(i=0;i<sizeof(email);i++)
		{
			if(email[i]==NULL)
			break;
			email[i]=tolower(email[i]);
		}
		lineNum++;  
		if(!(lineNum%100000))printf("\nRead the %d line: %s",lineNum,email);
		return 1;
		//printf("\n --%d--",i);
	}
        
	else
	{   
	    if(feof(fp))
	    {
    		printf("\nEnd of the file");
	        return -1;
    	}
	    else
	    {
    		printf("\nRead error");
    		exit(1);
    	}
		
	}
      
}


int main()
{

	char *strPool = malloc(sizeof(char)*20);
	char *checkedEmail = malloc(sizeof(char)*20);
	int checkedResult;
	printf("Please enter the email pool file you want to input: ");
	scanf("%s", strPool);
	char_transfer();
	initial();
	file_open(strPool);
	while(read_line()>0)
	{
		insert();
	}
	fclose(fp);
	printf("\nDone! finish inputing the email pool");
	printf("\n------------------------------------------------------");
	printf("\nPlease enter the checkedemail filename for search: ");
	scanf("%s", checkedEmail);
//	fileEnd=-1;
	lineNum = 1;
	file_open(checkedEmail);
	while(read_line()>0)
	{
		checkedResult=trie_check();
		if(checkedResult<0)
           printf("\nThe %d line: -NO-",lineNum-1);
        else
           printf("\nThe %d line: -YES-",lineNum-1);
	}
    fclose(fp);
    printf("\nDone! finish checking");
	printf("\n------------------------------------------------------");
	return 0;
}
