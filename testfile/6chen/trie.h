#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie树节点，包含指向左右节点的指针，和该节点是否为结束节点的标志
typedef struct Node
{
    struct Node* child;
    struct Node* nextsibling;
    char* ch;
}Node;

/*
* 释放Trie树占用内存
*/
void freeTree(Node* root);

/*
* 将字符串大写转换为小写
*/
int UpperTOLower(char** ch, int length);

/*
* 从节点中匹配待查询的字符串，如果节点中的字符串全部匹配，返回1；
* 待查询字符串全部匹配，返回2；全部匹配，返回3；否则返回-1
*/
int findNode(Node* ptr, char* lineMail);

/*
* 从构建好的Trie树中寻找待检测的字符串，并向文件checkedresult输出结果
* 返回找到的字符串个数
*/
int findMail(Node* root, char* checkedfile, char* checkresult);

/*
* 比较两个字符串从头开始相同位数
*/
int compareStr(char* str1, char* str2);

/*
* 构建Trie树，将一个email地址加入到Trie树中
*/
int buildRoot(Node** root, char* lineMail);

/*
* 构建Trie树，因内存不够，分为2次构建，构建一次查找一次
*/
int buildTree(Node* root, char* filePath);

#endif

