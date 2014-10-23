//
//  hash.h
//  trie_compress
//
//  Created by 黄岁 on 14-10-23.
//  Copyright (c) 2014年 黄岁. All rights reserved.
//

#ifndef HASH_H
#define HASH_H

typedef unsigned int (*phashfunc)(char*, unsigned int len);

unsigned int RSHash(char* str, unsigned int len);
unsigned int JSHash(char* str, unsigned int len);
unsigned int PJWHash(char* str, unsigned int len);
unsigned int ELFHash(char* str, unsigned int len);
unsigned int BKDRHash(char* str, unsigned int len);
unsigned int SDBMHash(char* str, unsigned int len);
unsigned int DJBHash(char* str, unsigned int len);
unsigned int DEKHash(char* str, unsigned int len);
unsigned int BPHash(char* str, unsigned int len);
unsigned int FNVHash(char* str, unsigned int len);
unsigned int APHash(char* str, unsigned int len);
unsigned int SAXHash(char *str, unsigned int len);


#endif