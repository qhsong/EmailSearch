
#include "trie.h"

/*
* 释放Trie树占用内存
*/
void freeTree(Node* root)
{
    if(root)
    {
        freeTree(root->child);
        freeTree(root->nextsibling);
        free(root->ch);
        free(root);
    }
}

/*
* 将字符串大写转换为小写
*/
int UpperTOLower(char** ch, int length)
{
    char tmp[length];
    int i = 0;
    char* ptr = *ch;
    for(; *ptr != '\r' && *ptr != '\n'; ptr++, i++)
    {
        if(*ptr >= 'A' && *ptr <= 'Z')
            tmp[i] = *ptr + 32;
        else if(*ptr < 45 || *ptr > 122)
            return 0;
        else
            tmp[i] = *ptr;
    }
    tmp[i]='\0';
    strcpy(*ch, tmp);
    return 1;
}

/*
* 比较两个字符串从头开始相同位数
*/
int compareStr(char* str1, char* str2)
{
    int count = 0;
    for(; str1 != '\0' && str2 != '\0'; str1++, str2++)
    {
        if(*str1 == *str2)
            count++;
        else
            break;
    }
    return count;
}

/*
* 从节点中匹配待查询的字符串，如果节点中的字符串全部匹配，返回1；
* 待查询字符串全部匹配，返回2；全部匹配，返回3；否则返回-1
*/
int findNode(Node* nodeptr, char* lineMail)
{
    int check = 0;
    char* ptr = nodeptr->ch;
    for(; *ptr != '\0' && *lineMail != '\0'; ptr++, lineMail++)
    {
        if(*ptr != *lineMail)
        {
            check = -1;
            break;
        }
    }
    if(check == 0)
    {
        if(*ptr == '\0' && *lineMail == '\0')
            check = 3;
        else if(*ptr == '\0' && *lineMail != '\0')
            check = 1;
        else if(*ptr != '\0' && *lineMail == '\0')
            check = 2;
    }
    return check;
}

/*
* 从构建好的Trie树中寻找待检测的字符串，并向文件checkedresult输出结果
* 返回找到的字符串个数
*/
int findMail(Node* root, char* checkedfile, char* checkedresult)
{
    int count = 0;
    Node* ptr = NULL;

    FILE* mailPool = fopen(checkedfile, "rt");
    if(!mailPool)
        return 0;

    FILE* checkresult = fopen(checkedresult, "wt");
    if(!checkresult)
        return 0;

    if(root->child)
    {
        char* lineMail = (char*)malloc(sizeof(char) * 320);
        int found = 0;
        while(fgets(lineMail, 320, mailPool))
        {
            if(!UpperTOLower(&lineMail, strlen(lineMail))){}
            else
            {
                ptr = root->child;
                while(*lineMail != '\0' && ptr)
                {
                    found = 0;
                    int check = findNode(ptr, lineMail);
                    if(check == -1)
                        ptr = ptr->nextsibling;
                    else if(check == 3)
                    {
                        found = 1;
                        count++;
                        break;
                    }
                    else if(check == 1)
                    {
                        int len = strlen(ptr->ch);
                        lineMail += len;
                        ptr = ptr->child;
                    }
                    else
                        break;
                }
                if(found)
                    fprintf(checkresult, "yes\r\n");
                else
                    fprintf(checkresult, "no\r\n");
            }
        }
    }
    fclose(mailPool);
    fclose(checkresult);
    return count;
}

/*
* 构建Trie树，将一个email地址加入到Trie树中
*/
int buildRoot(Node** ptr, char* lineMail)
{
    int n = 0;
    char tmp[321];
    Node* newChild = NULL;
    if(strlen(lineMail) == 0)
        return 1;
    else if(!(*ptr))
    {
        //printf("First build, lineMail is : %s\n", lineMail);
        (*ptr) = (Node*)malloc(sizeof(Node));
        (*ptr)->child = NULL; (*ptr)->nextsibling = NULL;
        (*ptr)->ch = (char*)malloc(sizeof(char)*strlen(lineMail) + 1);
        strcpy((*ptr)->ch, lineMail);
        //printf("First build, ptr->ch is : %s\n", (*ptr)->ch);
    }
    else
    {
        //printf("Not first build, lineMail is : %s\n", lineMail);
        n = compareStr((*ptr)->ch, lineMail);
        if(n > 0 && n < strlen((*ptr)->ch))
        {
            Node* newNode = (Node*)malloc(sizeof(Node));
            if(!newNode)
                return 0;
            newNode->child = (*ptr)->child;
            newNode->nextsibling = NULL;
            newNode->ch = (char*)malloc(sizeof(char)*(strlen((*ptr)->ch) - n + 1));
            strcpy(newNode->ch, (*ptr)->ch + n);
            //printf("Split, ptr->ch is : %s\n", (*ptr)->ch);
            //printf("Split, newNode->ch is : %s\n", newNode->ch);

            (*ptr)->child = newNode;
            //printf("%d\n", sizeof(char) * (n + 1));
            (*ptr)->ch = (char*)realloc((*ptr)->ch, sizeof(char) * (n + 1));

            strcpy(tmp, (*ptr)->ch);
            tmp[n] = '\0';
            strcpy((*ptr)->ch, tmp);
            //printf("Split complete, ptr->ch is : %s\n", (*ptr)->ch);

            if(strlen(lineMail) - n > 0)
            {
                newChild = (Node*)malloc(sizeof(Node));
                if(!newChild)
                    return 0;
                newChild->child = NULL; newChild->nextsibling = NULL;
                newChild->ch = (char*)malloc(sizeof(char) * (strlen(lineMail) - n + 1));
                strcpy(newChild->ch, lineMail + n);
                //printf("Split remain, newChild->ch is : %s\n", newChild->ch);
                newNode->nextsibling = newChild;
            }
        }
        else if(n == 0)
            buildRoot(&((*ptr)->nextsibling), lineMail);
        else
            buildRoot(&((*ptr)->child), lineMail + n);
    }
    return 1;
}

/*
* 构建Trie树
*/
int buildTree(Node* root, char* filePath)
{
    char* lineMail = NULL;
    if(!root)
        return 0;
    FILE* mailPool = fopen(filePath, "rt");
    if(!mailPool)
    {
        printf("Failed to open strpool.dat.\n");
        return 0;
    }
    lineMail = (char*)malloc(sizeof(char)*320);
    while(fgets(lineMail, 320, mailPool))
    {
        if(!UpperTOLower(&lineMail, strlen(lineMail)))
            continue;
        if(!buildRoot(&(root->child), lineMail))
            return 0;
    }

    fclose(mailPool);
    return 1;
}
