#include "line.h"
#include "bitmap.h"

_Thread_local struct Pixel current_color;

void set_color(uint32_t color)
{
	current_color.blue = color % 256;
	current_color.green = (color >> 8) % 256;
	current_color.red = (color >> 16) % 256;
}

void draw_line(uint16_t y, uint16_t right, uint16_t left)
{
	int start = WIDTH * y + left;
	for (int i = start; i <= start - left + right; i++) {
		bitmap[i] = current_color;
		/*
		struct Pixel *pixel = bitmap + i;
		pixel->red = 255;
		pixel->green = 0;
		pixel->blue = 0;
		*/
	}
}
