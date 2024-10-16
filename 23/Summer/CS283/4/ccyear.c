#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	CComp item;
	CComp* cc;
	FILE *fp;
	int i;
	int start, end;

	if(argc != 3) {
		fprintf(stderr, "Usage: ccyear start end\n");
		exit(1);
	}
		
	start = atoi(argv[1]);
	end =  atoi(argv[2]);

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
	for(int j = 0; j < i; j++){
		nitem = *(cc + j);
		fseek(fp, nitem.id* sizeof(CComp), SEEK_SET);

		if(nitem.year >= start && nitem.year <= end){
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
	exit(0);
}
