#include <stdlib.h>
#include <string.h>

#include "image.h"

void set_pix(size_t, size_t, uint8_t, uint8_t, uint8_t);

void line(size_t y, size_t right, size_t left)
{
	size_t start = image.width * y + right;
	for (int i = start; i < start + left; i++) {
		pixel_t *pixel = image.pixels + i;
		pixel->red = 255;
		pixel->green = 0;
		pixel->blue = 0;
	}
}

void draw()
{
	image.width = 100;
	image.height = 100;

	image.pixels = calloc(image.width * image.height, sizeof(pixel_t));
	
	memset(image.pixels, 'a', image.height*image.width*sizeof(uint8_t));

	line(50, 10, 80);
	line(51, 10, 80);
	line(52, 10, 80);
	line(53, 10, 80);
}
