#include <limits.h>
#include <string.h>

#include "bloom.h"
#include "hash.h"

//set and get bit value from bloomfilter vector
#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

//the vector to put the line read from file 
#define MAXLINE 1024
#define VECTOR_SIZE (23962*10000) 

//hash functions
phashfunc hash_funs[] = {RSHash, JSHash, PJWHash, ELFHash, 
				BKDRHash, SDBMHash, DJBHash, DEKHash,
				BPHash, FNVHash, APHash};
const int hash_len = 11;

/**
 * create bloom filter from mailfile
 * param: filename mailfile name
 */
BF *bloom_create(char *filename, int vector_size)
{
	//initilize the BF 
	BF *bf = (BF*)malloc(sizeof(BF));

	bf->size = vector_size;
	bf->bf_vector = malloc(sizeof(char) * (vector_size+1) );
	memset(bf->bf_vector, 0, vector_size);

	//read the mailfile line by line
	FILE *fp;
	char line[MAXLINE+1];

	if((fp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "File %s open error!\n", filename);
	}

	while((fgets(line, MAXLINE, fp)) != NULL)
	{
		//remove the newline char
		int line_len = strlen(line);
		if(line[line_len-1] == '\n')
			line[line_len-1] = '\0';
		if(line[line_len-2] == '\r')
			line[line_len-2] = '\0';
		//set the vector
		bloom_add(bf, line);
		//fputs(line, stdout);
	}

	fclose(fp);
	return bf;
}


/**
 * destroy the BF struct
 * param: bf		bloom filter struct pointer 
 */
int bloom_destroy(BF *bf)
{
	bf->size = 0;
	free(bf->bf_vector);
	bf->bf_vector = NULL;
	free(bf);
	bf = NULL;

	return 0;
}

/**
 * set vector bit of a mail by 11 hash functions
 * param: bf		bloom filter struct 
 * param: line		mailname
 */
int bloom_add(BF *bf, char *line)
{
	unsigned int hash_num = 0; 
	for(int i = 0; i < hash_len; ++i)
	{
		hash_num = (hash_funs[i])(line, strlen(line));	
		hash_num = hash_num % (bf->size*8); 
		SETBIT(bf->bf_vector, hash_num);
	}

	return 0;
}

/**
 * check if the mail in the mailfile 
 * param: bf		bloom filter vector 
 * param: line		mailname
 *
 * return: 1 if in or 0 not
 */
int bloom_check(BF *bf, char *line)
{
	unsigned int hash_num = 0; 
	for(int i = 0; i < hash_len; ++i)
	{
		hash_num = (hash_funs[i])(line, strlen(line));	
		hash_num = hash_num % (bf->size*8); 
		int flag = GETBIT(bf->bf_vector, hash_num);
		if(flag == 0)
			return 0;
	}

	return 1;
}
