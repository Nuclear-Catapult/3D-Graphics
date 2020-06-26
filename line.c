#include "line.h"
#include "bitmap.h"

void draw_line(int16_t y, int16_t right, int16_t left)
{
	int start = WIDTH * y + left;
	for (int i = start; i <= start - left + right; i++) {
		struct Pixel *pixel = bitmap + i;
		pixel->red = 255;
		pixel->green = 0;
		pixel->blue = 0;
	}
}
