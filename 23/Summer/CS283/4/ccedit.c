#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <string.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	CComp item;
	CComp* cc;
	FILE *fp;
	int id;
	int i;
	char* name;
	char* maker;
	char* cpu;
	char* year;
	char* desc;

	if(argc != 2) {
		fprintf(stderr, "Usage: ccedit id\n");
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

	name = (char*) malloc(32 * sizeof(char*));
	maker = (char*) malloc(16 * sizeof(char*));
	cpu = (char*) malloc(8 * sizeof(char*));
	year = (char*) malloc(5 * sizeof(char*));
	desc = (char*) malloc(192 * sizeof(char*));

	for(int j; j < i; j++){
		nitem = *(cc + j);
		fseek(fp, nitem.id * sizeof(CComp), SEEK_SET);
		if(nitem.id == id){
			printf("\n");
			printf("Name: %s\n", nitem.name);
			printf("Maker: %s\n", nitem.maker);
			printf("CPU: %s\n", nitem.cpu);
			printf("Year: %d\n", nitem.year);
			printf("ID: %d\n", nitem.id);
			printf("Desc: %s\n", nitem.desc); 
			printf("----------------\n");

			printf("\n--- Editing ---\n");
			printf("Edit name: ");
			fgets(name, 32, stdin);
			*(name + strlen(name) - 1) = '\0';
			printf("\nEdit maker: ");
			fgets(maker, 16, stdin);
			*(maker + strlen(maker) - 1) = '\0';
			printf("\nEdit year: ");
			fgets(year, 6, stdin);
			*(year + strlen(year) - 1) = '\0';
			printf("\nEdit CPU: ");
			fgets(cpu, 8, stdin);
			*(cpu + strlen(cpu) - 1) = '\0';
			printf("\nEdit description: ");
			fgets(desc, 192, stdin);
			*(desc + strlen(desc) - 1) = '\0';

			if(strcmp(name, "\0") != 0){
				strcpy(nitem.name, name);
			}

			if(strcmp(maker, "\0") != 0){
				strcpy(nitem.maker, maker);	
			}

			if(strcmp(cpu, "\0") != 0){
				strcpy(nitem.cpu, cpu);
			}

			if(strcmp(year, "\0") != 0){
				nitem.year = atoi(year);
			}

			if(strcmp(desc, "\0") != 0){
				strcpy(nitem.desc, desc);	
			}

			fwrite(&nitem, sizeof(CComp), 1, fp);
		}else{
			fwrite(&nitem, sizeof(CComp), 1, fp);
		}
	}
	
	flock(fileno(fp), LOCK_UN);
	fclose(fp);
	free(cc);
	free(name);
	free(maker);
	free(cpu);
	free(year);
	free(desc);
	exit(0);
}
