/**
	Author：AndrewPan,Sun
	date：2014.10.13~2014.10.14
	summary：完成trie树的插入，查找。
*/

#include "compress_trie.h"

void trie_node_init(trie_node **root)
{
    (*root)->is_str = (char)0;
    (*root)->num_of_bit = 0;
    (*root)->compress_of_bit = NULL;
    (*root)->point_of_zero = NULL;
    (*root)->point_of_one = NULL;
}

void compress(trie_node *root,char* bit_of_insert)
{
    int i,j,len_of_insert;
    len_of_insert = strlen(bit_of_insert);
    root->num_of_bit = len_of_insert;
    if(root->num_of_bit<=32)
    {
        int temp;
        for(i=len_of_insert-1,j=0;i>=0;i--,j++)
        {
            if(bit_of_insert[i] == '0')
            {
                clearbit(temp,j);
            }
            else
            {
                setbit(temp,j);
            }
        }
        root->compress_of_bit = (unsigned char*)temp;
    }
    else
    {
        root->compress_of_bit = (unsigned char*)malloc((len_of_insert%8)?(len_of_insert/8+1):(len_of_insert/8));
        for(i=len_of_insert-1,j=0;i>=0;i--,j++)
        {
            if(bit_of_insert[i] == '0')
            {
                clearbit(root->compress_of_bit[j/8],j%8);
            }
            else
            {
                setbit(root->compress_of_bit[j/8],j%8);
            }
        }
    }
}


int trie_insert(trie_node **root,char* bit_of_insert)
{
    int ret;
    char bit_of_pop[10000];
    if(root == NULL)
    {
        ret = 0;
    }
    else
    {
        if((*root)->num_of_bit == 0)
        {
            if(!(*bit_of_insert))
            {
                (*root)->is_str = (char)1;
                ret = 1;
            }
            else
            {
                if((*root)->is_str == 0
                   && (*root)->point_of_zero == NULL
                   && (*root)->point_of_one == NULL)
                {
                    compress((*root),bit_of_insert);
                    (*root)->is_str = (char)1;
                    ret = 1;
                }
                else
                {
                    if(*bit_of_insert == '0')
                    {
                        if((*root)->point_of_zero == NULL)
                        {
                            (*root)->point_of_zero = (trie_node*)malloc(sizeof(trie_node));
                            trie_node_init(&(*root)->point_of_zero);
                            //temp_of_new++;
                        }
                        ret = trie_insert(&(*root)->point_of_zero,bit_of_insert+1);
                    }
                    else
                    {
                        if((*root)->point_of_one == NULL)
                        {
                            (*root)->point_of_one = (trie_node*)malloc(sizeof(trie_node));
                            trie_node_init(&(*root)->point_of_one);
                            //temp_of_new++;
                        }
                        ret = trie_insert(&(*root)->point_of_one,bit_of_insert+1);
                    }
                }
            }
        }
        else
        {
            int ans_of_compare = compare_of_bit((*root),bit_of_insert);
            if(ans_of_compare == 0)
            {
                trie_node *father = (trie_node*)malloc(sizeof(trie_node));
                trie_node_init(&father);
                //temp_of_new++;
                pop_bit((*root),bit_of_pop,1);
                if(bit_of_pop[0] == '0')
                {
                    father->point_of_zero = (*root);
                }
                else
                {
                    father->point_of_one = (*root);
                }
                if(!(*bit_of_insert))
                {
                    father->is_str = (char)1;
                    ret = 1;
                }
                else
                {
                    if(*bit_of_insert == '0')
                    {
                        father->point_of_zero = (trie_node*)malloc(sizeof(trie_node));
                        trie_node_init(&father->point_of_zero);
                        //temp_of_new++;
                        ret = trie_insert(&father->point_of_zero,bit_of_insert+1);
                    }
                    else
                    {
                        father->point_of_one = (trie_node*)malloc(sizeof(trie_node));
                        trie_node_init(&father->point_of_one);
                        //temp_of_new++;
                        ret = trie_insert(&father->point_of_one,bit_of_insert+1);
                    }
                }
                (*root) = father;
            }
            else
            {
                if(ans_of_compare == (int)(*root)->num_of_bit
                   && ans_of_compare == strlen(bit_of_insert))
                {
                    (*root)->is_str = (char)1;
                    ret = 1;
                }
                else if(ans_of_compare == (int)(*root)->num_of_bit)
                {
                    bit_of_insert += ans_of_compare;
                    if(*bit_of_insert == '0')
                    {
                        if((*root)->point_of_zero == NULL)
                        {
                            (*root)->point_of_zero = (trie_node*)malloc(sizeof(trie_node));
                            trie_node_init(&(*root)->point_of_zero);
                            //temp_of_new++;
                        }
                        ret = trie_insert(&(*root)->point_of_zero,bit_of_insert+1);
                    }
                    else
                    {
                        if((*root)->point_of_one == NULL)
                        {
                            (*root)->point_of_one = (trie_node*)malloc(sizeof(trie_node));
                            trie_node_init(&(*root)->point_of_one);
                            //temp_of_new++;
                        }
                        ret = trie_insert(&(*root)->point_of_one,bit_of_insert+1);
                    }
                }
                else if(ans_of_compare == strlen(bit_of_insert))
                {
                    trie_node *father = (trie_node*)malloc(sizeof(trie_node));
                    trie_node_init(&father);
                    //temp_of_new++;
                    pop_bit((*root),bit_of_pop,ans_of_compare);
                    compress(father,bit_of_pop);
                    father->is_str = (char)1;
                    pop_bit((*root),bit_of_pop,1);
                    if(bit_of_pop[0] == '0')
                    {
                        father->point_of_zero = (*root);
                    }
                    else
                    {
                        father->point_of_one = (*root);
                    }
                    (*root) = father;
                }
                else
                {
                    trie_node *father = (trie_node*)malloc(sizeof(trie_node));
                    trie_node_init(&father);
                    //temp_of_new++;
                    pop_bit((*root),bit_of_pop,ans_of_compare);
                    compress(father,bit_of_pop);
                    pop_bit((*root),bit_of_pop,1);
                    bit_of_insert += ans_of_compare+1;

                    if(bit_of_pop[0] == '0')
                    {
                        father->point_of_zero = (*root);
                        father->point_of_one = (trie_node*)malloc(sizeof(trie_node));
                        trie_node_init(&father->point_of_one);
                        //temp_of_new++;
                        ret = trie_insert(&father->point_of_one,bit_of_insert);
                    }
                    else
                    {
                        father->point_of_one = (*root);
                        father->point_of_zero = (trie_node*)malloc(sizeof(trie_node));
                        trie_node_init(&father->point_of_zero);
                        //temp_of_new++;
                        ret = trie_insert(&father->point_of_zero,bit_of_insert);
                    }
                    (*root) = father;
                }
            }
        }
    }
    return ret;
}


int trie_search(trie_node *root,char *bit_of_search)
{
    trie_node *p = root;
    while(p!=NULL && *bit_of_search)
    {
        if(p->num_of_bit!=0)
        {
            if((int)p->num_of_bit == compare_of_bit(p,bit_of_search))
            {
                bit_of_search += (int)p->num_of_bit;
            }
            else
            {
                p=NULL;
                break;
            }
        }
        if(!(*bit_of_search))
        {
            break;
        }
        if(bit_of_search[0]=='0')
        {
            p = p->point_of_zero;
            bit_of_search++;
        }
        else if(bit_of_search[0]=='1')
        {
            p = p->point_of_one;
            bit_of_search++;
        }
        if(!(*bit_of_search) && p!=NULL && p->num_of_bit!=0)
        {
            p=NULL;
            break;
        }
    }
    if(p!=NULL)
    {
        return p->is_str;
    }
    else
    {
        return 0;
    }
}


void trie_delete(trie_node *root)
{
    if(root == NULL)
        return;
    trie_delete(root->point_of_zero);
    trie_delete(root->point_of_one);
    free(root);
}


int compare_of_bit(trie_node *root,char* bit_of_insert)
{
    int len_of_insert = strlen(bit_of_insert);
    int i,j,tempbit;
    if(root->num_of_bit<=32)
    {
        for(i=0,j=root->num_of_bit-1;i<len_of_insert && i<root->num_of_bit;i++,j--)
        {
            tempbit = getbit((int)root->compress_of_bit,j);
            if(bit_of_insert[i]-'0' != tempbit)
            {
                break;
            }
        }
    }
    else
    {
        for(i=0,j=root->num_of_bit-1;i<len_of_insert && i<root->num_of_bit;i++,j--)
        {
            tempbit = getbit(root->compress_of_bit[j/8],j%8);
            if(bit_of_insert[i]-'0' != tempbit)
            {
                break;
            }
        }
    }
    return i;
}

void pop_bit(trie_node *root,char* bit_of_pop,int len_of_pop)
{
    int i,j;
    short num_of_bit = root->num_of_bit - (short)len_of_pop;
    if(root->num_of_bit<=32)
    {
        for(i=0,j=root->num_of_bit-1;i<len_of_pop;i++,j--)
        {
            bit_of_pop[i] = getbit((int)root->compress_of_bit,j) +'0';
        }
        bit_of_pop[i] = '\0';
    }
    else
    {
        for(i=0,j=root->num_of_bit-1;i<len_of_pop;i++,j--)
        {
            bit_of_pop[i] = getbit(root->compress_of_bit[j/8],j%8) +'0';
        }
        bit_of_pop[i] = '\0';

        if(num_of_bit == 0)
        {
            free(root->compress_of_bit);
        }
        else if(num_of_bit<=32)
        {
            int temp;
            for(j=num_of_bit-1;j>=0;j--)
            {
                if(getbit(root->compress_of_bit[j/8],j%8) == 0)
                {
                    clearbit(temp,j);
                }
                else
                {
                    setbit(temp,j);
                }
            }
            free(root->compress_of_bit);
            root->compress_of_bit = (unsigned char*)temp;
        }
        else
        {
            unsigned char *p;
            short num_of_byte = (num_of_bit%8)?(num_of_bit/8+1):(num_of_bit/8);
            if(((root->num_of_bit%8)?(root->num_of_bit/8+1):(root->num_of_bit/8)) != num_of_byte)
            {
                p = (unsigned char*)malloc(num_of_byte);
                short i;
                for(i=0;i<num_of_byte;i++)
                {
                    p[i] = root->compress_of_bit[i];
                }
                free(root->compress_of_bit);
                root->compress_of_bit = p;
            }
        }
    }
    root->num_of_bit = num_of_bit;
}
