#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<stdio.h>
#include "trie.h"
#include<time.h>

#define MAX_STRLEN		325		//email_address 长度
#define KEY_WIDTH		41      //4+26+10			



//字符映射  - . _   number  alpha 
int 
char_trans(int ch)
{
	if(isdigit(ch))
	{
		ch=ch-'0'+4;
	}
	else if(isalpha(ch))
	{
		if(isupper(ch))
			ch=tolower(ch);
		ch-='a';
		ch+=14;// 4+10
	}
	else
	{
		switch(ch)
		{
			case '-':ch=1;break;
			case '.':ch=2;break;
			case '_':ch=3;break;
			case '@':ch=40;break;
			default:break;
		}
	}

	return ch;
}

typedef struct trie_node{

	char *str;
	int count;
	struct trie_node* next[KEY_WIDTH];

} trie_node;

static trie_node 
trie_root={NULL,0,{NULL}};

//for test  测试分配内存是否失败，line是失败后我想显示的读取的地址行数
void judge_node(trie_node *tmp,int line)
{
	if(tmp==NULL)
	{
		printf("line:%d\n",line);
		getchar();
	}
}
//上一个是节点，这个是字符串
void judge_str(char *str,int line)
{
	if(str==NULL)
	{
		printf("line:%d\n",line);
		getchar();
	}
}


int 
trie_insert(const char *word_key)
{
	trie_node *cur_p=&trie_root,*tmp=NULL,*new_node=NULL,*prefix_node=NULL;
	int i,j,prefix_flag=0;
	static int line;
	char prefix[MAX_STRLEN+1];
	char word[MAX_STRLEN+1];
	if(word_key[0]==0)
		return 0;
	//ignore the invalid address
	for(i=0;word_key[i]!='\0';++i)
	{
		if((word[i]=char_trans(word_key[i]))>40 || word[i]<=0)
			return 2;
	}
	word[i]=0;
	//search until can't  process
	for(i=0;cur_p->next[word[i]];)
	{
		tmp=cur_p->next[word[i]];
		for(j=0;tmp->str[j]==word[i];++j,++i)
		{
			if(tmp->str[j]==0)//bug 1
				break;
		}
		if(tmp->str[j]!='\0')//
		{
			memcpy(prefix,tmp->str,j);
			prefix_flag=1;
			prefix[j]='\0';
			break;
		}
		else if(word[i]=='\0')//遍历到此节点尾能组成一个单词
		{
			tmp->count++;
			return 1;
		}
		cur_p=tmp;
	}


	//i 表示word需要从第i个开始存
	if(!prefix_flag)//NULL节点，新建一个节点，存地址剩余部分
	{
		    new_node=calloc(1,sizeof(trie_node));
			//assert(new_node!=NULL);
			/*
			
			if(new_node==NULL)
			{
				printf("total:%d\n",line);
				//exit(1);
				return 24;
			}*/
			judge_node(new_node,line);
			new_node->str=malloc(strlen(word+i)+1);
		//	assert(new_node->str!=NULL);
			/*
			
			if(new_node->str==NULL)
			{
				printf("total:%d\n",line);
				//exit(1);
				return 24;
			}*/
			judge_str(new_node->str,line);
			strcpy(new_node->str,word+i);
			new_node->count+=1;//count
			cur_p->next[word[i]]=new_node;
	}
	else//前缀、以前的、现在的 
	{

		int prefix_len=strlen(prefix);

		prefix_node=calloc(1,sizeof(trie_node));
		//assert(prefix_node!=NULL && new_node!=NULL);
		/*
		if(prefix_node==NULL)
			{
				printf("total:%d\n",line);
				//exit(1);
				return 24;
			}
			*/
		judge_node(prefix_node,line);
		prefix_node->str=malloc(prefix_len+1);
	//	assert(prefix_node->str!=NULL && new_node->str!=NULL);
		judge_str(prefix_node->str,line);
		/*
		if(prefix_node->str==NULL)
			{
				printf("total:%d\n",line);
				//exit(1);
				return 24;
			}*/
		strcpy(prefix_node->str,prefix);
		cur_p->next[prefix[0]]=prefix_node;

		strcpy(prefix,tmp->str+prefix_len);
		/*
		memmove(tmp->str,tmp->str+prefix_len,strlen(tmp->str+prefix_len)+1);//保存以前剩下的字符串
		realloc(tmp->str,strlen(tmp->str)+1);*/
		tmp->str=malloc(strlen(prefix)+1);
		judge_str(tmp->str,line);
		//assert(tmp->str!=NULL);
		strcpy(tmp->str,prefix);
		prefix_node->next[tmp->str[0]]=tmp;

		if(word[i])//新节点有需要保存的
		{
			new_node=calloc(1,sizeof(trie_node));
			judge_node(new_node,line);
			//	assert(new_node!=NULL);
			new_node->str=malloc(strlen(word+i)+1);
			//assert(new_node->str!=NULL);
			judge_str(new_node->str,line);
			strcpy(new_node->str,word+i);
			prefix_node->next[new_node->str[0]]=new_node;
			new_node->count=1;
		}
		else
			prefix_node->count=1;//前缀就是一个地址
	}
	line+=1;	
	return 1;
}

int	
trie_lookup(const char *word)
{
	trie_node *cur_p=&trie_root,*tmp_node;
	int i,j,tmp_key;
	if(!word[0] || !cur_p)
		return 0;
	
	//search until can't  process
	for(i=0,tmp_key=char_trans(word[0]);word[i] && cur_p->next[tmp_key];)
	{
		tmp_node=cur_p->next[tmp_key];
		for(j=0,tmp_key=char_trans(word[i]);tmp_node->str[j]==tmp_key;++j,++i,tmp_key=char_trans(word[i]))
			if(tmp_node->str[j]==0 && tmp_node->count)
				return 1;
		cur_p=tmp_node;
	}
	return 0;
}
int delete_node;

void delete_trie(trie_node *root_p)
{
	int i;
	if(!root_p)
		return;
	for(i=1;i<KEY_WIDTH;++i)
	{
		if(root_p->next[i])
			delete_trie(root_p->next[i]);
	}
	if(root_p!=&trie_root)
	{
		//free(root_p->str);
		assert(root_p!=NULL);
		free(root_p);
		delete_node+=1;
	}
	else
	{
		memset(&trie_root,0,sizeof(trie_node));
	}
}
int 
trie_check()
{
	char buf[MAX_STRLEN+8];
	int  result_index[100]={0};
	int  test_index=0;
	int line=0,first_round=1;
	//time_t free_time=0,time_tmp;
	FILE* input_pool=fopen("/home/bupt/strpool.dat","r");
	FILE* dat_to_check=fopen("/home/bupt/checkedemail.dat","r");
	FILE* result=fopen("result.dat","w");
	assert(input_pool!=NULL && dat_to_check!=NULL && result!=NULL);
	while(fscanf(input_pool,"%s",buf)!=EOF)
	{
		test_index+=1;
		if(trie_insert(buf)==24)
		{
			puts(buf);
			getchar();
		}
		/*
		if(test_index%200000==0 || feof(input_pool))
		{
			fseek(dat_to_check,0,SEEK_SET);
			line=0;
			puts("insert interrupt");
			while(fscanf(dat_to_check,"%s",buf)!=EOF)
			{
				if(trie_lookup(buf))
					result_index[line]=1;//只写入1，默认是0
				line+=1;
			}
			time_tmp=time(NULL);
			delete_trie(&trie_root);
			free_time+=time(NULL)-time_tmp;
			printf("deleted:%d\n",delete_node);
		//	trie_insert(buf);//上一轮剩下的邮箱地址	
		}*/
	}
	//最后一次检查
	fseek(dat_to_check,0,SEEK_SET);
	line=0;
	while(fscanf(dat_to_check,"%s",buf)!=EOF)
	{
			
		if(trie_lookup(buf))
			result_index[line]=1;//只写入1，默认是0
		line+=1;
	}
	for(line=0;line<100;line+=1)
	{
		if(result_index[line])
		fputs("yes\n",result);
		else
		fputs("no\n",result);
	}
	fclose(dat_to_check);
	fclose(input_pool);
	fclose(result);
	//printf("释放空间用时:%umins %usecs\n",free_time/60,free_time%60);
	return 1;
}
