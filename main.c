#include<stdio.h>
#include<string.h>

#include"bloomfilter.h"

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[1024];
	char *p;
	
	if(argc<2) {
		fprintf(stderr, "ERROR: No word file specified\n");
		return EXIT_FAILURE;
	}

	return 0;
}