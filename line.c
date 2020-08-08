#include "line.h"
#include "bitmap.h"

_Thread_local struct Pixel current_color;

void set_color(uint32_t color)
{
	current_color.blue = color % 256;
	current_color.green = (color >> 8) % 256;
	current_color.red = (color >> 16) % 256;
}

void draw_line(uint16_t x, uint16_t y, uint16_t right, const union Triangle *t2D, const struct Triangle3D *t3D)
{
	int start = WIDTH * y;
	while (x++ <= right)
		bitmap[start+x] = current_color;
}
