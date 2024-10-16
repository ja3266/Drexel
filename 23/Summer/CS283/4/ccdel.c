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
	int id;
	int i;

	if(argc != 2) {
		fprintf(stderr, "Usage: ccdel id\n");
		exit(1);
	}

	fp = fopen("ccdb", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_SH);
	
	cc = (CComp*) malloc (20 * sizeof(CComp));

	id = atoi(argv[1]); 
	
	i = 0;
	fseek(fp, sizeof(CComp), SEEK_SET);
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		*(cc + i) = item;
		i++;
	}

	flock(fileno(fp), LOCK_UN);	
	fclose(fp);
	remove("ccdb");

	fp = fopen("ccdb", "w");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_EX);

	CComp nitem;

	for(int j; j < i; j++){
		nitem = *(cc + j);
		fseek(fp, nitem.id * sizeof(CComp), SEEK_SET);
		if(nitem.id != id){
			fwrite(&nitem, sizeof(CComp), 1, fp);
		}
	}
	
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	free(cc);
	exit(0);
}
