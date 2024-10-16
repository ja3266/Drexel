#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct PGMImage{
	int width;
	int height;
	int max;
	unsigned char* pixels;
}PGMImage;


int
main (int argc, char* argv[])
{
	int n;
	int scale;
	char pixel;


	PGMImage* original = (PGMImage*) malloc(sizeof(PGMImage));

	//Getting image header from stdin
	n = scanf("P5 %d %d %d", &(original->width), &(original->height), &(original->max));

	original->pixels = malloc(original->width * original->height * sizeof( unsigned char));

	for(int i = 0; i < (original->width * original->height)/sizeof(unsigned char); i++){
		*(original->pixels + i) = getc(stdin);
	}

		printf("P5\n%d %d\n%d\n", original->width, original->height, original->max);

	
	for(int i = 0; i < (original->width * original->height)/sizeof(unsigned char); i++ ){
		printf("%c", *(original->pixels + i));
	}

	
	PGMImage* image = (PGMImage*) malloc(sizeof(PGMImage));

	scale = original->width/300;
	image->width = original->width/scale;
	image->height = original->height/scale;
	image->max = original->max;



			
	
	free(original);
	exit(0);
}
