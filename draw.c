#include "triangle.h"
#include "bitmap.h"

int main()
{
	struct Triangle t = { .v1 = {100, 100},
			 .v2 = {400, 400},
			 .v3 = {300, 150} };
	draw_triangle(&t);
	write_bmp();
}
