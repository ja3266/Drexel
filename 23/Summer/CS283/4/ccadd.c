#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	CComp newcomp;
	FILE *fp;
	int size;

	if(argc != 7) {
		fprintf(stderr, "Usage: ccadd id name maker cpu year desc\n");
		exit(1);
	}
	
	if(strcmp(argv[1], "-a") == 0){

		fp = fopen("ccdb", "r");
		
		struct stat buf;
		fstat(fileno(fp), &buf);
		size = buf.st_size;
		newcomp.id = size/sizeof(CComp);
		fclose(fp);
		

	}else{
		newcomp.id = atoi(argv[1]);
	}
	strncpy(newcomp.name, argv[2], Nname-1);
	newcomp.name[Nname-1] = '\0';
	strncpy(newcomp.maker, argv[3], Nmaker-1);
	newcomp.maker[Nmaker-1] = '\0';
	strncpy(newcomp.cpu, argv[4], Ncpu-1);
	newcomp.cpu[Ncpu-1] = '\0';
	newcomp.year = atoi(argv[5]);
	strncpy(newcomp.desc, argv[6], Ndesc-1);
	newcomp.desc[Ndesc-1] = '\0';


	fp = fopen("ccdb", "r+");
	if(fp == NULL) {
		if(errno == ENOENT) {
			fp = fopen("ccdb", "w+");
			if(fp == NULL ) {
				perror("fopen");
				exit(2);
			}
		}
	}
	flock(fileno(fp), LOCK_EX);
	fseek(fp, newcomp.id * sizeof(CComp), SEEK_SET);
	fwrite(&newcomp, sizeof(CComp), 1, fp);
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	exit(0);
}
