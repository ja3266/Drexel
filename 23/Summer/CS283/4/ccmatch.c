#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include "cc.h"

char* substring(char[], int, int);

int
main(int argc, char *argv[])
{
	CComp item;
	CComp* cc;
	FILE *fp;
	int i;
	char* input;
	char* maker;
	char* desc;
	char* name; 

	if(argc != 2) {
		fprintf(stderr, "Usage: ccmatch string\n");
		exit(1);
	}

	input = (char*) malloc(192 * sizeof(char));

	strcpy(input, argv[1]);

	fp = fopen("ccdb", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_SH);
	
	cc = (CComp*) malloc (20 * sizeof(CComp));

	i = 0;
	fseek(fp, sizeof(CComp), SEEK_SET);
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		*(cc + i) = item;
		i++;
	}
	
	CComp nitem;
	for(int j; j < i; j++){
		nitem = *(cc + j);
		fseek(fp, nitem.id * sizeof(CComp), SEEK_SET);
		maker = strstr(nitem.maker, input);
		name = strstr(nitem.name, input);
		desc = strstr(nitem.desc, input);
		if(maker != NULL || name != NULL || desc != NULL){
			printf("\n");
			printf("Name: %s\n", nitem.name);
			printf("Maker: %s\n", nitem.maker);
			printf("CPU: %s\n", nitem.cpu);
			printf("Year: %d\n", nitem.year);
			printf("ID: %d\n", nitem.id);
			printf("Desc: %s\n", nitem.desc);
			printf("----------------\n");
		}
	}

		
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	free(cc);
	free(input);
	exit(0);
}
