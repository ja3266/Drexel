/* thumb.c - Assignment 2
*	Author - Jacob Andrew
* 	Date - 7/17/23
* 
*	Purpose - To read a Portable GreyMap (PGM) image in from stdin, and print
*				a thumbnail out to stdout.
*
*/

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

void freeImage(PGMImage* image);

int
main (int argc, char* argv[])
{
	int scale;
	char pixel;

//Creating original image

	PGMImage* original = (PGMImage*) malloc(sizeof(PGMImage));

	scanf("P5 %d %d %d", &(original->width), &(original->height), &(original->max));

	original->pixels = malloc(original->width * original->height * sizeof( unsigned char));

	for(int i = 0; i < (original->width * original->height)/sizeof(unsigned char); i++){
		*(original->pixels + i) = getc(stdin);
	}
	
//Creating thumbnail	
	PGMImage* image = (PGMImage*) malloc(sizeof(PGMImage));

	scale = original->width/300;
	image->width = original->width/scale;
	image->height = original->height/scale;
	image->max = original->max;
	image->pixels = malloc(image->width * image->height * sizeof(unsigned char));

	printf("P5\n%d %d\n%d\n", image->width, image->height, image->max);

	for(int row = 0; row < image->height/sizeof(unsigned char); row++){
		for(int col = 0; col < image->width/sizeof(unsigned char); col++){
			
			*(image->pixels + (row * image->width) + col) =  *(original->pixels + ((row* original->width) + col)*scale);
	
		}
	}
	

//Writing new image to stdout
	for(int i = 0; i < (image->width * image->height)/sizeof(unsigned char); i++){
		printf("%c", *(image->pixels + i));
	}

//Memory leaks bad!
	freeImage(image);
	freeImage(original);
	exit(0);
}

/* freeImage - frees an image and it's pixel array from memory
*
*	Inputs - PGMImage* image: image to be freed
*	Outputs - none 
*	Side-effects - Image an it's pixels are freed from memory
*
*/
void
freeImage(PGMImage* image){

	free(image->pixels);
	free(image);
}
