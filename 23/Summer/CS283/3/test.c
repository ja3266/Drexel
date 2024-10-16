#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char* argv[])
{
	char* filename;

	filename = (char*) malloc(sizeof(char) * 256);

	fread(filename, 256, 1, stdin);	

	printf("%s\n", filename);

	free(filename);
}
