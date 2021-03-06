#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "hash.h"
#include "bloom.h"
#include <time.h>



int main(int argc, char *argv[])
{
	clock_t start =  clock();	
	int vector_size = 29952500;
	char *mails = "/home/bupt/strpool.dat";
	char *check_mails = "/home/bupt/checkedemail.dat";
	char *result = "result.dat";

	if(argc > 1)
		vector_size = atoi(argv[1]);
	if(argc > 2)
		mails = argv[2];
	if(argc > 3)
		check_mails = argv[3];
	if(argc > 4)
		result = argv[4];

	BF *bf = bloom_create(mails, vector_size);

	FILE *fp;
	FILE *fpw;
	const int MAXLINE = 1024;
	char line[MAXLINE+1];
	if((fp = fopen(check_mails, "r")) == NULL)
	{
		fprintf(stderr, "File %s open error!\n", check_mails);
	}
	if((fpw = fopen(result, "w")) == NULL)
	{
		fprintf(stderr, "File result.txt open error!\n");
	}

	int no_count = 0;
	while((fgets(line, MAXLINE, fp)) != NULL)
	{
		//remove the newline char
		int line_len = strlen(line);
		if(line[line_len-1] == '\n')
			line[line_len-1] = '\0';
		if(line[line_len-2] == '\r')
			line[line_len-2] = '\0';

		if(bloom_check(bf, line))
		{
			fprintf(fpw, "yes\n", line);
		}
		else
		{
			no_count++;
			fprintf(fpw, "no\n", line);
		}
	}

	fclose(fp);
	fclose(fpw);
	
	bloom_destroy(bf);	

	printf("%f\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}
