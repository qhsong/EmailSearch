#include<limits.h>
#include <string.h>
#include "bloom.h"
#include "hash.h"

#define SETBIT(a, n) (a[n/CHAR_BIT] |= (1<<(n%CHAR_BIT)))
#define GETBIT(a, n) (a[n/CHAR_BIT] & (1<<(n%CHAR_BIT)))

//char *hash_table;

BF *bloom_create(int size) {
	BF *bloomfilter = malloc(sizeof(BF));
	bloomfilter->size = size;
	int char_size = size / CHAR_BIT + 1;
	bloomfilter->hash_table = malloc(char_size);
	memset(bloomfilter->hash_table, 0, char_size);
	return bloomfilter;
}

int bloom_destroy(BF* bloomfilter) {
	free(bloomfilter->hash_table);
	free(bloomfilter);
	return 0;
}

int bloom_add(BF *bloomfilter, char *str) {
	long long hash_value = RSHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = JSHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = PJWHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = ELFHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = BKDRHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = SDBMHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = DJBHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = DEKHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = BPHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = FNVHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	hash_value = APHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	SETBIT(bloomfilter->hash_table, hash_value);

	return 0;
}

int bloom_check(BF *bloomfilter, char *str) {
	int flag = 1;
	long long hash_value = RSHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && (GETBIT(bloomfilter->hash_table, hash_value)));

	hash_value = JSHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = PJWHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = ELFHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = BKDRHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = SDBMHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = DJBHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = DEKHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = BPHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = FNVHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));

	hash_value = APHash(str, (unsigned int) strlen(str));
	hash_value %= bloomfilter->size;
	flag = (flag && GETBIT(bloomfilter->hash_table, hash_value));
	return flag;
}
